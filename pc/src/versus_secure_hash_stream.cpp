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
    CopyDigest(Digest, (const BYTE *)Context.State, DigestSize);
    memset(&Context, 0, sizeof(Context));
}

void SecureHashAlgorithm1::ByteReverse(DWORD *Data, DWORD Length)
{
    const DWORD LowBytes = 0x00ff00ff;
    for (DWORD Words = Length / sizeof(DWORD); Words; --Words) {
        const DWORD Word = *Data;
        const DWORD Up = Word << 8;
        const DWORD Down = Word >> 8;
        // Select alternate bytes from each shift, then exchange the two halfwords.
        const DWORD Swapped = Up ^ ((Down ^ Up) & LowBytes);
        *Data++ = (Swapped << 16) | (Swapped >> 16);
    }
}
