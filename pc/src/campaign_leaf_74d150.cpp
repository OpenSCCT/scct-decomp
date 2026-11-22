// campaign_leaf_74d150.cpp -- free function at VA 0x1104d150: when the global at VA 0x1132eab0 is
// set, passes it to the imported stdcall function whose address sits at VA 0x110b7330. All names
// are invented.

extern void* GUnk_1132eab0;
extern "C" __declspec(dllimport) int __stdcall Unk_110b7330(void* Handle);

// Unk_1104d150
void Unk_1104d150()
{
    if ( GUnk_1132eab0 )
    {
        Unk_110b7330(GUnk_1132eab0);
    }
}
