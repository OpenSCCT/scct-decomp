// campaign_leaf_75beb0.cpp -- one function at file offset 0x75beb0, preferred VA 0x1105beb0. It
// allocates a 0x1c-byte buffer at 0x14 through the stdcall function at VA 0x1103c830; when that
// fails it reports "Problem while Allocating memory." through the stdcall function at VA
// 0x1103c7f0 and sets the state at 0x4 to 0x13. Otherwise it stores the buffer at 0x2c and 0x30,
// its size at 0x24, clears the word at 0x1c, passes the words at 0x18 and 0x20 and the size to the
// stdcall function at VA 0x11094a50, sets the state to 3 and runs the method at VA 0x1105af50;
// when the state is then not 0x13 and the word at 0x1c is set, it sets the state to 4 and runs
// the method at VA 0x1105bdd0. The class and member names are invented; the offsets and the
// addresses are the binary's.

void* __stdcall Unk_1103c830(unsigned int Size);
void __stdcall Unk_1103c7f0(int Level, const char* Message, int Kind);
int __stdcall Unk_11094a50(int First, int Second, int Size);

class UnkType_1105beb0
{
public:
    void Unk_1105af50();
    void Unk_1105bdd0();
    void Unk_1105beb0();

    int unk_0;
    int unk_4;
    unsigned char unk_8[0x14 - 0x8];
    void* unk_14;
    int unk_18;
    int unk_1c;
    int unk_20;
    int unk_24;
    unsigned char unk_28[0x2c - 0x28];
    void* unk_2c;
    void* unk_30;
};

// UnkType_1105beb0::Unk_1105beb0
void UnkType_1105beb0::Unk_1105beb0()
{
    unk_14 = Unk_1103c830(0x1c);
    if ( unk_14 == 0 )
    {
        Unk_1103c7f0(10, "Problem while Allocating memory.", 3);
        unk_4 = 0x13;
        return;
    }
    unk_30 = unk_14;
    unk_2c = unk_14;
    unk_24 = 0x1c;
    unk_1c = 0;
    Unk_11094a50(unk_18, unk_20, 0x1c);
    unk_4 = 3;
    Unk_1105af50();
    if ( unk_4 != 0x13 && unk_1c != 0 )
    {
        unk_4 = 4;
        Unk_1105bdd0();
    }
}
