// campaign_leaf_7719e0.cpp -- one function at file offset 0x7719e0, preferred VA 0x110719e0. It
// grows its buffers for a count: when the capacity at 0x30 is below the count times the stride at
// 0x34 it stores that size there and reallocates the buffer at 0x28 to it, and reallocates the
// buffer at 0x2c to the count's words (through the stdcall functions at VA 0x1103c850, or VA
// 0x1103c830 for a buffer not yet allocated). It then stores the count at 0x24. The class,
// method and member names are invented; the offsets and the addresses are the binary's.

void* __stdcall Unk_1103c830(unsigned int Size);
void* __stdcall Unk_1103c850(void* Pointer, unsigned int Size);

class UnkType_110719e0
{
public:
    void Unk_110719e0(unsigned int* Count);

    unsigned char unk_0[0x24];
    unsigned int unk_24;
    void* unk_28;
    int* unk_2c;
    unsigned int unk_30;
    unsigned int unk_34;
};

// UnkType_110719e0::Unk_110719e0
void UnkType_110719e0::Unk_110719e0(unsigned int* Count)
{
    unsigned int Size;

    Size = unk_34 * *Count;
    if ( unk_30 < Size )
    {
        unk_30 = Size;
        if ( unk_28 != 0 )
        {
            unk_28 = Unk_1103c850(unk_28, Size);
        }
        else
        {
            unk_28 = Unk_1103c830(Size);
        }
        if ( unk_2c != 0 )
        {
            unk_2c = (int*)Unk_1103c850(unk_2c, *Count * sizeof(int));
        }
        else
        {
            unk_2c = (int*)Unk_1103c830(*Count * sizeof(int));
        }
    }
    unk_24 = *Count;
}
