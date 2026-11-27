#include "versus_secure_hash_algorithm_1.h"

extern "C" void *__cdecl memcpy(void *, const void *, unsigned int);
extern "C" void *__cdecl memset(void *, int, unsigned int);
#pragma intrinsic(memcpy, memset)

void SecureHashAlgorithm1::Init()
{
    memset(&Context, 0, sizeof(Context));
    Context.State[0] = 0x67452301;
    Context.State[1] = 0xefcdab89;
    Context.State[2] = 0x98badcfe;
    Context.State[3] = 0x10325476;
    Context.State[4] = 0xc3d2e1f0;
    Context.Count[0] = Context.Count[1] = 0;
}

void SecureHashAlgorithm1::Update(const BYTE *Input, DWORD Length)
{
    DWORD Bits = Context.Count[0];
    if ((Context.Count[0] = Bits + (Length << 3)) < Bits)
        ++Context.Count[1];
    Context.Count[1] += Length >> 29;

    DWORD Used = (Bits >> 3) & (BlockSize - 1);
    if (Used) {
        DWORD Free = BlockSize - Used;
        BYTE *Tail = Context.Buffer.Bytes + Used;
        if (Length < Free) {
            memcpy(Tail, Input, Length);
            return;
        }
        memcpy(Tail, Input, Free);
        ByteReverse(Context.Buffer.Words, BlockSize);
        Transform(Context.State, Context.Buffer.Words);
        Input += Free;
        Length -= Free;
    }

    while (Length >= BlockSize) {
        memcpy(Context.Buffer.Bytes, Input, BlockSize);
        ByteReverse(Context.Buffer.Words, BlockSize);
        Transform(Context.State, Context.Buffer.Words);
        Input += BlockSize;
        Length -= BlockSize;
    }
    memcpy(Context.Buffer.Bytes, Input, Length);
}

void SecureHashAlgorithm1::Final(BYTE *Digest)
{
    INT Used = ((INT)Context.Count[0] >> 3) & (BlockSize - 1);
    BYTE *Tail = Context.Buffer.Bytes + Used;
    *Tail++ = 0x80;

    INT Free = BlockSize - 1 - Used;
    if (Free < 8) {
        memset(Tail, 0, Free);
        ByteReverse(Context.Buffer.Words, BlockSize);
        Transform(Context.State, Context.Buffer.Words);
        memset(Context.Buffer.Bytes, 0, BlockSize - 8);
    } else {
        memset(Tail, 0, Free - 8);
    }
    Context.Buffer.Words[14] = Context.Count[1];
    Context.Buffer.Words[15] = Context.Count[0];
    ByteReverse(Context.Buffer.Words, BlockSize - 8);
    Transform(Context.State, Context.Buffer.Words);
    CopyDigest(Digest, Context.State, DigestSize);
    memset(&Context, 0, sizeof(Context));
}

void SecureHashAlgorithm1::ByteReverse(DWORD *Data, DWORD Length)
{
    for (DWORD Words = Length / sizeof(DWORD); Words; --Words) {
        DWORD Word = *Data;
        Word = ((Word & 0xff00ff00) >> 8) | ((Word & 0x00ff00ff) << 8);
        *Data++ = (Word >> 16) | (Word << 16);
    }
}

void SecureHashAlgorithm1::CopyDigest(BYTE *Output, const DWORD *Words, DWORD Length)
{
    for (DWORD Word = 0, Byte = 0; Byte < Length; ++Word, Byte += 4) {
        Output[Byte + 3] = (BYTE)(Words[Word] & 0xff);
        Output[Byte + 2] = (BYTE)((Words[Word] >> 8) & 0xff);
        Output[Byte + 1] = (BYTE)((Words[Word] >> 16) & 0xff);
        Output[Byte] = (BYTE)((Words[Word] >> 24) & 0xff);
    }
}
