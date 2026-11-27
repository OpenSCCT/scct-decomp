// Versus RTTI names this class and both allocator bases. Method names describe their SHA-1 operations.
#ifndef VERSUS_SECURE_HASH_ALGORITHM_1_H
#define VERSUS_SECURE_HASH_ALGORITHM_1_H

#include "versus_build.h"
#include "unreal_types.h"

#include "versus_cldata.h"

class clExtalloc_Override_Baseclass : public virtual ExtAlloc::OverrideAllocOperators {
public:
    virtual ~clExtalloc_Override_Baseclass();
};

class SecureHashAlgorithm1 : public clExtalloc_Override_Baseclass {
public:
    virtual ~SecureHashAlgorithm1();
    void Init();
    void Update(const BYTE *Input, DWORD Length);
    void Final(BYTE *Digest);

private:
    union Block {
        enum { Size = 64 };
        BYTE Bytes[Size];
        DWORD Words[Size / sizeof(DWORD)];
    };
    enum { BlockSize = sizeof(Block), DigestSize = 20 };
    struct {
        DWORD State[5];
        DWORD Count[2];
        Block Buffer;
    } Context;

    void Transform(DWORD *State, const DWORD *Data);
    void ByteReverse(DWORD *Data, DWORD Length);
    void CopyDigest(BYTE *Output, const DWORD *Words, DWORD Length);
};
#endif
