#include "versus_md5.h"

extern "C" void *__cdecl memcpy(void *, const void *, unsigned int);
extern "C" void *__cdecl memset(void *, int, unsigned int);
#pragma intrinsic(memcpy, memset)

static BYTE Padding[64] = {0x80};

MD5::MD5()
{
    Init();
}

void MD5::Init()
{
    Finalized = false;
    Count[0] = 0;
    Count[1] = 0;
    memset(Buffer, 0, sizeof(Buffer));
    memset(Digest, 0, sizeof(Digest));
    State[0] = 0x67452301;
    State[1] = 0xefcdab89;
    State[2] = 0x98badcfe;
    State[3] = 0x10325476;
}

void MD5::Update(const BYTE *Input, DWORD Length)
{
    if (Finalized)
        return;

    DWORD Used = (Count[0] >> 3) & (BlockSize - 1);
    if ((Count[0] += Length << 3) < (Length << 3))
        ++Count[1];
    Count[1] += Length >> 29;

    DWORD Free = BlockSize - Used;
    DWORD Consumed;
    if (Length >= Free) {
        memcpy(Buffer + Used, Input, Free);
        Transform(Buffer);
        for (Consumed = Free; Consumed + BlockSize - 1 < Length; Consumed += BlockSize)
            Transform(Input + Consumed);
        Used = 0;
    } else {
        Consumed = 0;
    }
    memcpy(Buffer + Used, Input + Consumed, Length - Consumed);
}

void MD5::Final(BYTE *Output)
{
    if (Finalized)
        return;

    BYTE LengthBytes[8];
    Encode(LengthBytes, Count, sizeof(LengthBytes));
    DWORD Used = (Count[0] >> 3) & (BlockSize - 1);
    DWORD PaddingLength = (Used < 56) ? (56 - Used) : (120 - Used);
    Update(Padding, PaddingLength);
    Update(LengthBytes, sizeof(LengthBytes));
    Encode(Digest, State, DigestSize);
    Finalized = true;
    memcpy(Output, Digest, DigestSize);
    // The retail finalizer clears the first byte of each internal byte array.
    memset(Buffer, 0, sizeof(*Buffer));
    memset(Digest, 0, sizeof(*Digest));
}

void __stdcall MD5::Encode(BYTE *Output, const DWORD *Input, DWORD Length)
{
    for (DWORD Word = 0, Byte = 0; Byte < Length; ++Word, Byte += 4) {
        Output[Byte] = (BYTE)(Input[Word] & 0xff);
        Output[Byte + 1] = (BYTE)((Input[Word] >> 8) & 0xff);
        Output[Byte + 2] = (BYTE)((Input[Word] >> 16) & 0xff);
        Output[Byte + 3] = (BYTE)((Input[Word] >> 24) & 0xff);
    }
}

void __stdcall MD5::Decode(DWORD *Output, const BYTE *Input, DWORD Length)
{
    for (DWORD Word = 0, Byte = 0; Byte < Length; ++Word, Byte += 4) {
        Output[Word] = (DWORD)Input[Byte] |
                       ((DWORD)Input[Byte + 1] << 8) |
                       ((DWORD)Input[Byte + 2] << 16) |
                       ((DWORD)Input[Byte + 3] << 24);
    }
}
