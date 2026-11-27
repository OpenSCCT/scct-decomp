#include "versus_d3d_texture.h"
#include "versus_canvas_materials.h"
#include "unreal_math.h"

void appMemcpy(void *Dest, const void *Src, INT Count);

UBOOL IsDXTCompressed(ETextureFormat Format)
{
    return Format == TEXF_DXT1 || Format == TEXF_DXT3 || Format == TEXF_DXT5;
}

BYTE *TextureDataAddress(ETextureFormat Format, BYTE *Data, INT Pitch, INT X, INT Y)
{
    switch (Format) {
    case TEXF_P4:       return Data + (Y / 2) * Pitch + X / 2;
    case TEXF_DXT1:     return Data + (Y / 4) * Pitch + X * 2;
    case TEXF_DXT3:
    case TEXF_DXT5:     return Data + (Y / 4) * Pitch + X * 4;
    case TEXF_RGBA7:
    case TEXF_RGBA8:    return Data + Y * Pitch + X * 4;
    case TEXF_RGB8:
    case TEXF_RRRGGGBBB: return Data + Y * Pitch + X * 3;
    case TEXF_RGB16:
    case TEXF_G16:      return Data + Y * Pitch + X * 2;
    case TEXF_P8:
    case TEXF_L8:       return Data + Y * Pitch + X;
    default:            return Data;
    }
}

UBOOL UD3DRenderDevice::SupportsTextureFormat(ETextureFormat Format) const
{
    switch (Format) {
    case TEXF_DXT1: return SupportsDXT1;
    case TEXF_DXT3: return SupportsDXT3;
    case TEXF_DXT5: return SupportsDXT5;
    case TEXF_RGB8:
    case TEXF_RGBA8: return !Use16bitTextures;
    default: return 1;
    }
}

INT TextureRowBytes(ETextureFormat format, INT width)
{
    switch (format) {
    case TEXF_P4: case TEXF_DXT1: return width / 2;
    case TEXF_RGBA7: case TEXF_RGBA8: return width * 4;
    case TEXF_RGB16: case TEXF_G16: return width * 2;
    case TEXF_RGB8: return width * 3;
    case TEXF_DXT3: case TEXF_DXT5: case TEXF_P8: case TEXF_L8: return width;
    default: return 0;
    }
}

static inline _WORD To4444(FColor pixel)
{
    return (((pixel.A & 0xf0) * 16 + (pixel.R & 0xf0)) * 16) + (pixel.G & 0xf0) + (pixel.B >> 4);
}

UBOOL FD3DTexture::Cache(FBaseTexture *source)
{
    UBOOL failed = 0;
    INT first = source->GetFirstMip();
    INT sourceWidth = source->GetWidth();
    INT sourceHeight = source->GetHeight();
    INT mipCount = source->GetNumMips();
    ETextureFormat format = source->GetFormat();
    if (format == TEXF_P8 || format == TEXF_P4 || format == TEXF_G16 || format == TEXF_RGBA7)
        format = TEXF_RGBA8;
    FCompositeTexture *composite = source->GetCompositeTextureInterface();
    FCubemap *cube = source->GetCubemapInterface();
    FTexture *bitmap = source->GetTextureInterface();
    FRenderTarget *target = source->GetRenderTargetInterface();
    INT maxMips = 0;
    for (INT size = sourceWidth < sourceHeight ? sourceWidth : sourceHeight; size > 0; size >>= 1)
        ++maxMips;
    if (mipCount > maxMips)
        mipCount = maxMips;
    // The retail build snapshots the locked viewport before examining the cube map.
    UViewport *viewport = RenDev->LockedViewport;
    if (cube && !RenDev->SupportsCubemaps) {
        bitmap = cube->GetFace(0);
        cube = 0;
    }
    D3DFORMAT destFormat;
    if (format == TEXF_RGBA8)
        destFormat = RenDev->Use16bitTextures ? D3DFMT_A4R4G4B4 : D3DFMT_A8R8G8B8;
    else if (format == TEXF_DXT1)
        destFormat = D3DFMT_DXT1;
    else if (format == TEXF_DXT3)
        destFormat = D3DFMT_DXT3;
    else
        destFormat = format == TEXF_DXT5 ? D3DFMT_DXT5 : D3DFMT_UNKNOWN;
    UBOOL downsample = 0;
    while ((sourceWidth >> first) > RenDev->MaxTextureWidth || (sourceHeight >> first) > RenDev->MaxTextureHeight) {
        if (++first >= mipCount)
            downsample = 1;
    }
    if (downsample)
        first = 0;
    INT width = sourceWidth >> first, height = sourceHeight >> first;
    INT stepX = 1, stepY = 1;
    if (downsample) {
        if (width > RenDev->MaxTextureWidth) width = RenDev->MaxTextureWidth;
        if (height > RenDev->MaxTextureHeight) height = RenDev->MaxTextureHeight;
        stepX = sourceWidth / width;
        stepY = sourceHeight / height;
    }
    if (!height || !width) {
        if (source->GetTextureInterface())
            source->GetTextureInterface()->GetUTexture();  // Used by the editor's zero-dimension diagnostic.
        CubeTexture = 0;
        Texture = 0;
    } else if (composite) {
        INT count = composite->GetNumChildren();
        if (!Texture || CachedWidth != width || CachedHeight != height || CachedFirstMip != 0 ||
            CachedMipCount != 1 || CachedFormat != destFormat) {
            if (Texture) Texture->Release();
            if (format == TEXF_RGBA8 && RenDev->Use16bitTextures)
                destFormat = D3DFMT_R5G6B5;
            RenDev->Direct3DDevice8->CreateTexture(width, height, 1, 0, destFormat, D3DPOOL_MANAGED, &Texture);
            ChildRevisions.Empty(count);
        }
        if (ChildRevisions.Num() != count) {
            ChildRevisions.Empty(count);
            ChildRevisions.AddZeroed(sizeof(INT), count);
            D3DLOCKED_RECT rect;
            Texture->LockRect(0, &rect, 0, 0);
            BYTE *data = static_cast<BYTE *>(rect.pBits);
            INT pitch = rect.Pitch;
            if (destFormat == D3DFMT_R5G6B5) {
                pitch = sourceWidth * 4;
                data = new BYTE[pitch * sourceHeight];
            }
            for (INT i = 0; i < count; ++i) {
                INT x = 0, y = 0;
                FTexture *child = composite->GetChild(i, &x, &y);
                INT revision = child->GetRevision();
                child->GetTextureData(0, TextureDataAddress(format, data, pitch, x, y), pitch, format, 0);
                ChildRevisions(i) = revision;
            }
            if (destFormat == D3DFMT_R5G6B5) {
                FColor *from = reinterpret_cast<FColor *>(data);
                _WORD *to = static_cast<_WORD *>(rect.pBits);
                for (INT y = 0; y < height; ++y) {
                    for (INT x = 0; x < width; ++x) {
                        FColor color = *from;
                        from += 2;
                        *to++ = ((color.R & 0xf8) * 32 + (color.G & 0xfc)) * 8 + (color.B >> 3);
                    }
                    from += width * 2;
                }
                GMalloc->Free(data);
            }
            Texture->UnlockRect(0);
        }
    } else if (cube && RenDev->SupportsCubemaps && RenDev->SupportsTextureFormat(format)) {
        if (!CubeTexture || CachedWidth != width || CachedHeight != height || CachedFirstMip != first ||
            CachedMipCount != mipCount || CachedFormat != destFormat) {
            if (CubeTexture) CubeTexture->Release();
            RenDev->Direct3DDevice8->CreateCubeTexture(width, RenDev->SupportsMipCubeMap ? mipCount - first : 1,
                0, destFormat, D3DPOOL_MANAGED, &CubeTexture);
        }
        INT last = RenDev->SupportsMipCubeMap ? mipCount : first + 1;
        for (INT mip = first; mip < last; ++mip) {
            for (INT face = 0; face < 6; ++face) {
                FTexture *faceTexture = cube->GetFace(face);
                if (faceTexture) {
                    D3DLOCKED_RECT rect;
                    CubeTexture->LockRect(static_cast<D3DCUBEMAP_FACES>(face), mip - first, &rect, 0, 0);
                    faceTexture->GetTextureData(mip, rect.pBits, rect.Pitch, format, 0);
                    CubeTexture->UnlockRect(static_cast<D3DCUBEMAP_FACES>(face), mip - first);
                }
            }
        }
    } else if (target) {
        if (!Texture || CachedWidth != width || CachedHeight != height || CachedFirstMip != first ||
            CachedMipCount != mipCount || CachedFormat != destFormat) {
            if (Texture) Texture->Release();
            for (INT attempt = 0; attempt < 2; ++attempt) {
                if (RenDev->Direct3DDevice8->CreateTexture(width, height, mipCount - first, D3DUSAGE_RENDERTARGET,
                        destFormat, D3DPOOL_DEFAULT, &Texture) >= 0) {
                    Texture->GetSurfaceLevel(0, &RenderTargetSurface);
                    break;
                }
                RenDev->Direct3DDevice8->ResourceManagerDiscardBytes(0);
            }
            if (attempt == 2) failed = 1;
        }
        if (!failed && (!DepthStencilSurface || CachedWidth != width || CachedHeight != height ||
                       CachedFirstMip != first || CachedMipCount != mipCount)) {
            if (DepthStencilSurface) DepthStencilSurface->Release();
            for (INT attempt = 0; attempt < 2; ++attempt) {
                if (RenDev->Direct3DDevice8->CreateDepthStencilSurface(width, height, (D3DFORMAT)RenDev->DepthFormat,
                        D3DMULTISAMPLE_NONE, &DepthStencilSurface) >= 0) break;
                RenDev->Direct3DDevice8->ResourceManagerDiscardBytes(0);
            }
            if (attempt == 2) failed = 1;
        }
        if (failed) {
            if (RenderTargetSurface) RenderTargetSurface->Release();
            if (Texture) Texture->Release();
            if (DepthStencilSurface) DepthStencilSurface->Release();
            Texture = 0;
            CubeTexture = 0;
            RenderTargetSurface = 0;
            DepthStencilSurface = 0;
        }
    } else if (bitmap) {
        BYTE *data = 0;
        UBOOL convert = 0, readRGBA = 0;
        if (!RenDev->SupportsTextureFormat(format) && (IsDXTCompressed(format) || RenDev->Use16bitTextures)) {
            if (format == TEXF_RGBA8) {
                destFormat = D3DFMT_A4R4G4B4;
                INT pitch;
                if (downsample) {
                    data = new BYTE[sourceWidth * sourceHeight * 4];
                    pitch = sourceWidth * 4;
                } else {
                    data = new BYTE[width * height * 4];
                    pitch = width * 4;
                }
                bitmap->GetTextureData(first, data, pitch, TEXF_RGBA8, 0);
                readRGBA = 1;
            } else {
                format = bitmap->GetUTexture()->ConvertDXT(first, !RenDev->SupportsDXT1, 0, &data);
                if (format == TEXF_DXT1) {
                    destFormat = D3DFMT_DXT1;
                    convert = 0;
                } else if (format == TEXF_RGBA8) {
                    convert = 1;
                    destFormat = RenDev->Use16bitTextures ? D3DFMT_A4R4G4B4 : D3DFMT_A8R8G8B8;
                }
            }
        }
        if (!Texture || CachedWidth != width || CachedHeight != height || CachedFirstMip != first ||
            CachedMipCount != mipCount || CachedFormat != destFormat) {
            if (Texture) Texture->Release();
            RenDev->Direct3DDevice8->CreateTexture(width, height, mipCount - first, 0, destFormat, D3DPOOL_MANAGED, &Texture);
        }
        for (INT mip = first; mip < mipCount; ++mip) {
            INT level = mip - first;
            INT w = width >> level, h = height >> level;
            D3DLOCKED_RECT rect;
            Texture->LockRect(level, &rect, 0, 0);
            if (data) {
                INT rowWidth = w, rows = h, rowBytes;
                if (IsDXTCompressed(format)) {
                    if (rowWidth < 4) rowWidth = 4;
                    rows = (rows < 4 ? 4 : rows) / 4;
                    rowBytes = TextureRowBytes(format, rowWidth) * 4;
                } else {
                    rowBytes = TextureRowBytes(format, w);
                }
                if (RenDev->Use16bitTextures) {
                    rowBytes /= 2;
                    FColor *from = reinterpret_cast<FColor *>(data);
                    _WORD *to = reinterpret_cast<_WORD *>(data);
                    if (downsample) {
                        for (INT y = 0; y < rows; ++y) {
                            for (INT x = 0; x < rowWidth; ++x) {
                                *to++ = To4444(*from);
                                from += stepX;
                            }
                            from += (stepY - 1) * sourceWidth;
                        }
                    } else {
                        for (INT y = 0; y < rows; ++y)
                            for (INT x = 0; x < rowWidth; ++x)
                                *to++ = To4444(*from++);
                    }
                }
                if (rect.Pitch == rowBytes) {
                    appMemcpy(rect.pBits, data, rowBytes * rows);
                } else {
                    BYTE *to = static_cast<BYTE *>(rect.pBits), *from = data;
                    for (INT y = 0; y < rows; ++y) {
                        appMemcpy(to, from, rowBytes);
                        to += rect.Pitch;
                        from += rowBytes;
                    }
                }
                GMalloc->Free(data);
                data = 0;
                if (mip < mipCount - 1) {
                    if (readRGBA) {
                        data = static_cast<BYTE *>(GMalloc->Malloc(w * h * 4, L"new"));
                        bitmap->GetTextureData(mip + 1, data, w * 2, format, 0);
                    } else {
                        bitmap->GetUTexture()->ConvertDXT(mip + 1, convert, 0, &data);
                    }
                }
            } else if (!RenDev->Use16bitTextures) {
                bitmap->GetTextureData(mip, rect.pBits, rect.Pitch, format, mip >= RenDev->FirstColoredMip);
            }
            Texture->UnlockRect(level);
        }
        GMalloc->Free(data);
    } else {
        CubeTexture = 0;
        Texture = 0;
    }
    CachedRevision = source->GetRevision();
    CachedWidth = width;
    CachedHeight = height;
    CachedFirstMip = first;
    CachedMipCount = mipCount;
    CachedFormat = destFormat;
    return failed;
}
