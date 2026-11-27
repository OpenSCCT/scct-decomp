#ifndef VERSUS_MIPMAP_H
#define VERSUS_MIPMAP_H

#include "versus_lazy_archive.h"

template<> class TLazyArray<BYTE> : public FLazyLoader, public TArray<BYTE> {
public:
    void Load();
    void Unload() {
        if (SavedPos < 0) {
            Empty();
            SavedPos = -SavedPos;
        }
    }
};

struct FMipmapBase {
    BYTE *DataPtr;
    INT USize, VSize;
    BYTE UBits, VBits;
};

struct FMipmap : public FMipmapBase {
    TLazyArray<BYTE> DataArray;
};

#endif
