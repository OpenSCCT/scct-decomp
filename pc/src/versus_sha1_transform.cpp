#include "versus_secure_hash_algorithm_1.h"

static inline DWORD RotateLeft(DWORD Value, unsigned Count)
{
    return (Value << Count) | (Value >> (32 - Count));
}

static inline DWORD Choose(DWORD B, DWORD C, DWORD D)
{
    return (B & (C ^ D)) ^ D;
}

static inline DWORD Parity(DWORD B, DWORD C, DWORD D)
{
    return B ^ C ^ D;
}

static inline DWORD Majority(DWORD B, DWORD C, DWORD D)
{
    return (B & C) | ((B | C) & D);
}

#define SHA1_ROUND(Mix, Constant, A, B, C, D, E, Word) \
    do { \
        (E) += RotateLeft((A), 5) + Mix((B), (C), (D)) + (Word) + (Constant); \
        (B) = RotateLeft((B), 30); \
    } while (0)

#define INPUT_ROUND(Mix, K, A, B, C, D, E, I) \
    do { \
        Words[I] = Data[I]; \
        SHA1_ROUND(Mix, K, A, B, C, D, E, Words[I]); \
    } while (0)

// Sixteen words hold the rolling SHA-1 schedule. Each expansion replaces the oldest word.
#define EXPANDED_ROUND(Mix, K, A, B, C, D, E, I, Expanded) \
    do { \
        Expanded = Words[((I) - 3) & 15] ^ Words[((I) - 8) & 15] ^ \
                   Words[((I) - 14) & 15] ^ Words[(I) & 15]; \
        Words[(I) & 15] = RotateLeft(Expanded, 1); \
        SHA1_ROUND(Mix, K, A, B, C, D, E, Words[(I) & 15]); \
    } while (0)

void SecureHashAlgorithm1::Transform(DWORD *State, const DWORD *Data)
{
    DWORD A = State[0];
    DWORD B = State[1];
    DWORD C = State[2];
    DWORD D = State[3];
    DWORD E = State[4];

    Block Schedule;
    DWORD *Words = Schedule.Words;
    DWORD Expanded;

    const DWORD ChooseConstant = 0x5a827999;
    const DWORD ParityConstant = 0x6ed9eba1;
    const DWORD MajorityConstant = 0x8f1bbcdc;
    const DWORD FinalConstant = 0xca62c1d6;

    INPUT_ROUND(Choose, ChooseConstant, A, B, C, D, E, 0);
    INPUT_ROUND(Choose, ChooseConstant, E, A, B, C, D, 1);
    INPUT_ROUND(Choose, ChooseConstant, D, E, A, B, C, 2);
    INPUT_ROUND(Choose, ChooseConstant, C, D, E, A, B, 3);
    INPUT_ROUND(Choose, ChooseConstant, B, C, D, E, A, 4);
    INPUT_ROUND(Choose, ChooseConstant, A, B, C, D, E, 5);
    INPUT_ROUND(Choose, ChooseConstant, E, A, B, C, D, 6);
    INPUT_ROUND(Choose, ChooseConstant, D, E, A, B, C, 7);
    INPUT_ROUND(Choose, ChooseConstant, C, D, E, A, B, 8);
    INPUT_ROUND(Choose, ChooseConstant, B, C, D, E, A, 9);
    INPUT_ROUND(Choose, ChooseConstant, A, B, C, D, E, 10);
    INPUT_ROUND(Choose, ChooseConstant, E, A, B, C, D, 11);
    INPUT_ROUND(Choose, ChooseConstant, D, E, A, B, C, 12);
    INPUT_ROUND(Choose, ChooseConstant, C, D, E, A, B, 13);
    INPUT_ROUND(Choose, ChooseConstant, B, C, D, E, A, 14);
    INPUT_ROUND(Choose, ChooseConstant, A, B, C, D, E, 15);
    EXPANDED_ROUND(Choose, ChooseConstant, E, A, B, C, D, 16, Expanded);
    EXPANDED_ROUND(Choose, ChooseConstant, D, E, A, B, C, 17, Expanded);
    EXPANDED_ROUND(Choose, ChooseConstant, C, D, E, A, B, 18, Expanded);
    EXPANDED_ROUND(Choose, ChooseConstant, B, C, D, E, A, 19, Expanded);

    EXPANDED_ROUND(Parity, ParityConstant, A, B, C, D, E, 20, Expanded);
    EXPANDED_ROUND(Parity, ParityConstant, E, A, B, C, D, 21, Expanded);
    EXPANDED_ROUND(Parity, ParityConstant, D, E, A, B, C, 22, Expanded);
    EXPANDED_ROUND(Parity, ParityConstant, C, D, E, A, B, 23, Expanded);
    EXPANDED_ROUND(Parity, ParityConstant, B, C, D, E, A, 24, Expanded);
    EXPANDED_ROUND(Parity, ParityConstant, A, B, C, D, E, 25, Expanded);
    EXPANDED_ROUND(Parity, ParityConstant, E, A, B, C, D, 26, Expanded);
    EXPANDED_ROUND(Parity, ParityConstant, D, E, A, B, C, 27, Expanded);
    EXPANDED_ROUND(Parity, ParityConstant, C, D, E, A, B, 28, Expanded);
    EXPANDED_ROUND(Parity, ParityConstant, B, C, D, E, A, 29, Expanded);
    EXPANDED_ROUND(Parity, ParityConstant, A, B, C, D, E, 30, Expanded);
    EXPANDED_ROUND(Parity, ParityConstant, E, A, B, C, D, 31, Expanded);
    EXPANDED_ROUND(Parity, ParityConstant, D, E, A, B, C, 32, Expanded);
    EXPANDED_ROUND(Parity, ParityConstant, C, D, E, A, B, 33, Expanded);
    EXPANDED_ROUND(Parity, ParityConstant, B, C, D, E, A, 34, Expanded);
    EXPANDED_ROUND(Parity, ParityConstant, A, B, C, D, E, 35, Expanded);
    EXPANDED_ROUND(Parity, ParityConstant, E, A, B, C, D, 36, Expanded);
    EXPANDED_ROUND(Parity, ParityConstant, D, E, A, B, C, 37, Expanded);
    EXPANDED_ROUND(Parity, ParityConstant, C, D, E, A, B, 38, Expanded);
    EXPANDED_ROUND(Parity, ParityConstant, B, C, D, E, A, 39, Expanded);

    EXPANDED_ROUND(Majority, MajorityConstant, A, B, C, D, E, 40, Expanded);
    EXPANDED_ROUND(Majority, MajorityConstant, E, A, B, C, D, 41, Expanded);
    EXPANDED_ROUND(Majority, MajorityConstant, D, E, A, B, C, 42, Expanded);
    EXPANDED_ROUND(Majority, MajorityConstant, C, D, E, A, B, 43, Expanded);
    EXPANDED_ROUND(Majority, MajorityConstant, B, C, D, E, A, 44, Expanded);
    EXPANDED_ROUND(Majority, MajorityConstant, A, B, C, D, E, 45, Expanded);
    EXPANDED_ROUND(Majority, MajorityConstant, E, A, B, C, D, 46, Expanded);
    EXPANDED_ROUND(Majority, MajorityConstant, D, E, A, B, C, 47, Expanded);
    EXPANDED_ROUND(Majority, MajorityConstant, C, D, E, A, B, 48, Expanded);
    EXPANDED_ROUND(Majority, MajorityConstant, B, C, D, E, A, 49, Expanded);
    EXPANDED_ROUND(Majority, MajorityConstant, A, B, C, D, E, 50, Expanded);
    EXPANDED_ROUND(Majority, MajorityConstant, E, A, B, C, D, 51, Expanded);
    EXPANDED_ROUND(Majority, MajorityConstant, D, E, A, B, C, 52, Expanded);
    EXPANDED_ROUND(Majority, MajorityConstant, C, D, E, A, B, 53, Expanded);
    EXPANDED_ROUND(Majority, MajorityConstant, B, C, D, E, A, 54, Expanded);
    EXPANDED_ROUND(Majority, MajorityConstant, A, B, C, D, E, 55, Expanded);
    EXPANDED_ROUND(Majority, MajorityConstant, E, A, B, C, D, 56, Expanded);
    EXPANDED_ROUND(Majority, MajorityConstant, D, E, A, B, C, 57, Expanded);
    EXPANDED_ROUND(Majority, MajorityConstant, C, D, E, A, B, 58, Expanded);
    EXPANDED_ROUND(Majority, MajorityConstant, B, C, D, E, A, 59, Expanded);

    EXPANDED_ROUND(Parity, FinalConstant, A, B, C, D, E, 60, Expanded);
    EXPANDED_ROUND(Parity, FinalConstant, E, A, B, C, D, 61, Expanded);
    EXPANDED_ROUND(Parity, FinalConstant, D, E, A, B, C, 62, Expanded);
    EXPANDED_ROUND(Parity, FinalConstant, C, D, E, A, B, 63, Expanded);
    EXPANDED_ROUND(Parity, FinalConstant, B, C, D, E, A, 64, Expanded);
    EXPANDED_ROUND(Parity, FinalConstant, A, B, C, D, E, 65, Expanded);
    EXPANDED_ROUND(Parity, FinalConstant, E, A, B, C, D, 66, Expanded);
    EXPANDED_ROUND(Parity, FinalConstant, D, E, A, B, C, 67, Expanded);
    EXPANDED_ROUND(Parity, FinalConstant, C, D, E, A, B, 68, Expanded);
    EXPANDED_ROUND(Parity, FinalConstant, B, C, D, E, A, 69, Expanded);
    EXPANDED_ROUND(Parity, FinalConstant, A, B, C, D, E, 70, Expanded);
    EXPANDED_ROUND(Parity, FinalConstant, E, A, B, C, D, 71, Expanded);
    EXPANDED_ROUND(Parity, FinalConstant, D, E, A, B, C, 72, Expanded);
    EXPANDED_ROUND(Parity, FinalConstant, C, D, E, A, B, 73, Expanded);
    EXPANDED_ROUND(Parity, FinalConstant, B, C, D, E, A, 74, Expanded);
    EXPANDED_ROUND(Parity, FinalConstant, A, B, C, D, E, 75, Expanded);
    EXPANDED_ROUND(Parity, FinalConstant, E, A, B, C, D, 76, Expanded);
    EXPANDED_ROUND(Parity, FinalConstant, D, E, A, B, C, 77, Expanded);
    EXPANDED_ROUND(Parity, FinalConstant, C, D, E, A, B, 78, Expanded);
    EXPANDED_ROUND(Parity, FinalConstant, B, C, D, E, A, 79, Expanded);

    State[0] += A;
    State[1] += B;
    State[2] += C;
    State[3] += D;
    State[4] += E;
}
