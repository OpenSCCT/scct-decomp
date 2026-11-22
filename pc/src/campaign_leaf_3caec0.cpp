// campaign_leaf_3caec0.cpp -- a free function at VA 0x10ccaec0 that converts its wide string
// argument with the function at VA 0x10cccc70 and returns atof (the C runtime's, named in
// pc/evidence/library-functions.tsv) of the result. The function names other than atof are
// invented; the addresses are the binary's.

extern "C" double __cdecl atof(const char* Text);

const char* Unk_10cccc70(const unsigned short* Text);

// Unk_10ccaec0
double Unk_10ccaec0(const unsigned short* Text)
{
    return atof(Unk_10cccc70(Text));
}
