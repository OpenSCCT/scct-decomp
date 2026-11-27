#include "windows_dispatch_types.h"

static const UINT RedBlueMask = 0x00ff00ff;
static const UINT AlphaGreenMask = 0xff00ff00;
static const UINT GreenMask = 0x0000ff00;

static inline UINT *NextRow(UINT *row, UINT pitch)
{
    return reinterpret_cast<UINT *>(reinterpret_cast<BYTE *>(row) + pitch);
}

static inline UINT RoundedRedBlueSum(const UINT *top, const UINT *bottom)
{
    return (top[0] & RedBlueMask) + (top[1] & RedBlueMask)
         + (bottom[0] & RedBlueMask) + (bottom[1] & RedBlueMask) + 0x00020002;
}

LONG c_BoxFilter2D_A8R8G8B8(UINT *dst, UINT *src, UINT width, UINT height,
                            UINT srcPitch, UINT dstPitch)
{
    UINT *end = NextRow(src, height * srcPitch);
    for (; src < end; dst = NextRow(dst, dstPitch), src = NextRow(src, 2 * srcPitch)) {
        UINT *out = dst;
        UINT *top = src;
        UINT *bottom = NextRow(src, srcPitch);
        for (; top < src + width; top += 2, bottom += 2) {
            UINT redBlue = RoundedRedBlueSum(top, bottom) >> 2;
            // Shift each high-byte channel before adding so the alpha sum fits.
            UINT alphaGreen = ((top[0] & AlphaGreenMask) >> 2) + ((top[1] & AlphaGreenMask) >> 2)
                            + ((bottom[0] & AlphaGreenMask) >> 2) + ((bottom[1] & AlphaGreenMask) >> 2)
                            + 0x00800080;
            *out++ = (redBlue & RedBlueMask) | (alphaGreen & AlphaGreenMask);
        }
    }
    return 0;
}

LONG c_BoxFilter2D_X8R8G8B8(UINT *dst, UINT *src, UINT width, UINT height,
                            UINT srcPitch, UINT dstPitch)
{
    UINT *end = NextRow(src, height * srcPitch);
    for (; src < end; dst = NextRow(dst, dstPitch), src = NextRow(src, 2 * srcPitch)) {
        UINT *out = dst;
        UINT *top = src;
        UINT *bottom = NextRow(src, srcPitch);
        for (; top < src + width; top += 2, bottom += 2) {
            UINT redBlue = RoundedRedBlueSum(top, bottom);
            UINT green = (top[0] & GreenMask) + (top[1] & GreenMask)
                       + (bottom[0] & GreenMask) + (bottom[1] & GreenMask) + 0x00000200;
            *out++ = ((redBlue & (RedBlueMask << 2)) | (green & (GreenMask << 2))) >> 2;
        }
    }
    return 0;
}
