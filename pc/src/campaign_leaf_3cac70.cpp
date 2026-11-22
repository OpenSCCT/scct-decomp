// campaign_leaf_3cac70.cpp -- a free function at VA 0x10ccac70 that returns rand() scaled by
// 1/32767, a float from 0 to 1. The function name is invented; rand is the C runtime's (its object
// is named in pc/evidence/library-functions.tsv).

extern "C" int __cdecl rand(void);

// Unk_10ccac70
float Unk_10ccac70()
{
    return rand() * (1.0f / 32767.0f);
}
