#ifndef VERSUS_MD5_H
#define VERSUS_MD5_H

#include "versus_build.h"
#include "unreal_types.h"
#include "versus_cl_extalloc.h"

class MD5 : public clExtalloc_Override_Baseclass {
public:
    MD5();
    virtual ~MD5();
    void Init();
    void Update(const BYTE *Input, DWORD Length);
    void Final(BYTE *Output);

private:
    enum { BlockSize = 64, DigestSize = 16 };
    DWORD State[4];
    DWORD Count[2];
    BYTE Buffer[BlockSize];
    BYTE Digest[DigestSize];
    bool Finalized;

    void Transform(const BYTE *Block);
    static void __stdcall Encode(BYTE *Output, const DWORD *Input, DWORD Length);
    static void __stdcall Decode(DWORD *Output, const BYTE *Input, DWORD Length);
    static inline void __stdcall II(DWORD &A, DWORD B, DWORD C, DWORD D, DWORD Word, DWORD Shift, DWORD Constant);
};
#endif
