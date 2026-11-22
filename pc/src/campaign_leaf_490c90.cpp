// campaign_leaf_490c90.cpp -- free function at VA 0x10d90c90: when the global pointer at
// VA 0x1131a6b0 is set, frees it with the operator delete at VA 0x10d87b90 and clears it. All
// names are invented.

struct UnkType_1131a6b0
{
    int unk_00;
};

void operator delete(void* Pointer);

extern UnkType_1131a6b0* GUnk_1131a6b0;

// Unk_10d90c90
void Unk_10d90c90()
{
    if (GUnk_1131a6b0) {
        delete GUnk_1131a6b0;
        GUnk_1131a6b0 = 0;
    }
}
