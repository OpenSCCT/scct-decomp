// versus_mid_267a20.cpp -- Versus file offset 0x267a20-0x2683b4 (VA 0x10b67a20): one MD5 block
// transform, a __thiscall method that updates the four chaining words at +0x8 of the object.
// FUN_10b68410 decodes the 64-byte block into 16 words. Steps 58 to 64 call the out-of-line
// round-4 step FUN_10b68460, as the retail calls do; steps 1 to 57 are expanded inline.
// guess: the algorithm is MD5 (RFC 1321): the table, shifts and word order are its own.
// Class and member names are invented, see the unit's identification.

typedef unsigned long UINT4;

#define MD5_ROTL(x, n) ((UINT4)(((x) << (n)) | ((x) >> (32 - (n)))))
#define MD5_F(x, y, z) (((x) & (y)) | (~(x) & (z)))
#define MD5_G(x, y, z) (((x) & (z)) | ((y) & ~(z)))
#define MD5_H(x, y, z) ((x) ^ (y) ^ (z))
#define MD5_I(x, y, z) ((y) ^ ((x) | ~(z)))
#define MD5_STEP(f, a, b, c, d, x, s, t)     { (a) += f((b), (c), (d)) + (x) + (t); (a) = MD5_ROTL((a), (s)); (a) += (b); }

extern "C" {
// Decodes Length bytes of little-endian input into Output (stdcall, three stack arguments).
void __stdcall FUN_10b68410(UINT4 *Output, const unsigned char *Input, unsigned int Length);
// One round-4 step, out of line: *a = b + rotl(*a + I(b, c, d) + x + t, s) (stdcall, seven arguments).
void __stdcall FUN_10b68460(UINT4 *a, UINT4 b, UINT4 c, UINT4 d, UINT4 x, UINT4 s, UINT4 t);
}

// Placeholder class: the owning class of this method is unknown.
class UnkType_10b67a20
{
public:
    unsigned char unk_0[8];     // not touched by this method
    UINT4 unk_8[4];             // the chaining words, read and written by this method
    void Unk_10b67a20(const unsigned char *Block);
};

// UnkType_10b67a20::Unk_10b67a20 -- VA 0x10b67a20: the MD5 transform of one 64-byte block.
void UnkType_10b67a20::Unk_10b67a20(const unsigned char *Block)
{
    UINT4 a = unk_8[0];
    UINT4 b = unk_8[1];
    UINT4 c = unk_8[2];
    UINT4 d = unk_8[3];
    UINT4 x[16];
    FUN_10b68410(x, Block, 64);
    // Round 1
    MD5_STEP(MD5_F, a, b, c, d, x[0], 7, 0xd76aa478);
    MD5_STEP(MD5_F, d, a, b, c, x[1], 12, 0xe8c7b756);
    MD5_STEP(MD5_F, c, d, a, b, x[2], 17, 0x242070db);
    MD5_STEP(MD5_F, b, c, d, a, x[3], 22, 0xc1bdceee);
    MD5_STEP(MD5_F, a, b, c, d, x[4], 7, 0xf57c0faf);
    MD5_STEP(MD5_F, d, a, b, c, x[5], 12, 0x4787c62a);
    MD5_STEP(MD5_F, c, d, a, b, x[6], 17, 0xa8304613);
    MD5_STEP(MD5_F, b, c, d, a, x[7], 22, 0xfd469501);
    MD5_STEP(MD5_F, a, b, c, d, x[8], 7, 0x698098d8);
    MD5_STEP(MD5_F, d, a, b, c, x[9], 12, 0x8b44f7af);
    MD5_STEP(MD5_F, c, d, a, b, x[10], 17, 0xffff5bb1);
    MD5_STEP(MD5_F, b, c, d, a, x[11], 22, 0x895cd7be);
    MD5_STEP(MD5_F, a, b, c, d, x[12], 7, 0x6b901122);
    MD5_STEP(MD5_F, d, a, b, c, x[13], 12, 0xfd987193);
    MD5_STEP(MD5_F, c, d, a, b, x[14], 17, 0xa679438e);
    MD5_STEP(MD5_F, b, c, d, a, x[15], 22, 0x49b40821);
    // Round 2
    MD5_STEP(MD5_G, a, b, c, d, x[1], 5, 0xf61e2562);
    MD5_STEP(MD5_G, d, a, b, c, x[6], 9, 0xc040b340);
    MD5_STEP(MD5_G, c, d, a, b, x[11], 14, 0x265e5a51);
    MD5_STEP(MD5_G, b, c, d, a, x[0], 20, 0xe9b6c7aa);
    MD5_STEP(MD5_G, a, b, c, d, x[5], 5, 0xd62f105d);
    MD5_STEP(MD5_G, d, a, b, c, x[10], 9, 0x02441453);
    MD5_STEP(MD5_G, c, d, a, b, x[15], 14, 0xd8a1e681);
    MD5_STEP(MD5_G, b, c, d, a, x[4], 20, 0xe7d3fbc8);
    MD5_STEP(MD5_G, a, b, c, d, x[9], 5, 0x21e1cde6);
    MD5_STEP(MD5_G, d, a, b, c, x[14], 9, 0xc33707d6);
    MD5_STEP(MD5_G, c, d, a, b, x[3], 14, 0xf4d50d87);
    MD5_STEP(MD5_G, b, c, d, a, x[8], 20, 0x455a14ed);
    MD5_STEP(MD5_G, a, b, c, d, x[13], 5, 0xa9e3e905);
    MD5_STEP(MD5_G, d, a, b, c, x[2], 9, 0xfcefa3f8);
    MD5_STEP(MD5_G, c, d, a, b, x[7], 14, 0x676f02d9);
    MD5_STEP(MD5_G, b, c, d, a, x[12], 20, 0x8d2a4c8a);
    // Round 3
    MD5_STEP(MD5_H, a, b, c, d, x[5], 4, 0xfffa3942);
    MD5_STEP(MD5_H, d, a, b, c, x[8], 11, 0x8771f681);
    MD5_STEP(MD5_H, c, d, a, b, x[11], 16, 0x6d9d6122);
    MD5_STEP(MD5_H, b, c, d, a, x[14], 23, 0xfde5380c);
    MD5_STEP(MD5_H, a, b, c, d, x[1], 4, 0xa4beea44);
    MD5_STEP(MD5_H, d, a, b, c, x[4], 11, 0x4bdecfa9);
    MD5_STEP(MD5_H, c, d, a, b, x[7], 16, 0xf6bb4b60);
    MD5_STEP(MD5_H, b, c, d, a, x[10], 23, 0xbebfbc70);
    MD5_STEP(MD5_H, a, b, c, d, x[13], 4, 0x289b7ec6);
    MD5_STEP(MD5_H, d, a, b, c, x[0], 11, 0xeaa127fa);
    MD5_STEP(MD5_H, c, d, a, b, x[3], 16, 0xd4ef3085);
    MD5_STEP(MD5_H, b, c, d, a, x[6], 23, 0x04881d05);
    MD5_STEP(MD5_H, a, b, c, d, x[9], 4, 0xd9d4d039);
    MD5_STEP(MD5_H, d, a, b, c, x[12], 11, 0xe6db99e5);
    MD5_STEP(MD5_H, c, d, a, b, x[15], 16, 0x1fa27cf8);
    MD5_STEP(MD5_H, b, c, d, a, x[2], 23, 0xc4ac5665);
    // Round 4
    MD5_STEP(MD5_I, a, b, c, d, x[0], 6, 0xf4292244);
    MD5_STEP(MD5_I, d, a, b, c, x[7], 10, 0x432aff97);
    MD5_STEP(MD5_I, c, d, a, b, x[14], 15, 0xab9423a7);
    MD5_STEP(MD5_I, b, c, d, a, x[5], 21, 0xfc93a039);
    MD5_STEP(MD5_I, a, b, c, d, x[12], 6, 0x655b59c3);
    MD5_STEP(MD5_I, d, a, b, c, x[3], 10, 0x8f0ccc92);
    MD5_STEP(MD5_I, c, d, a, b, x[10], 15, 0xffeff47d);
    MD5_STEP(MD5_I, b, c, d, a, x[1], 21, 0x85845dd1);
    MD5_STEP(MD5_I, a, b, c, d, x[8], 6, 0x6fa87e4f);
    FUN_10b68460(&d, a, b, c, x[15], 10, 0xfe2ce6e0);
    FUN_10b68460(&c, d, a, b, x[6], 15, 0xa3014314);
    FUN_10b68460(&b, c, d, a, x[13], 21, 0x4e0811a1);
    FUN_10b68460(&a, b, c, d, x[4], 6, 0xf7537e82);
    FUN_10b68460(&d, a, b, c, x[11], 10, 0xbd3af235);
    FUN_10b68460(&c, d, a, b, x[2], 15, 0x2ad7d2bb);
    FUN_10b68460(&b, c, d, a, x[9], 21, 0xeb86d391);
    unk_8[0] += a;
    unk_8[1] += b;
    unk_8[2] += c;
    unk_8[3] += d;
}
