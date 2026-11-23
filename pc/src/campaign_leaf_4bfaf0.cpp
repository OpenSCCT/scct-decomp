// campaign_leaf_4bfaf0.cpp -- one function at file offset 0x4bfaf0, preferred VA 0x10dbfaf0.
// It stores Priority at offset 0x10 and passes it to SetThreadPriority with the thread handle the
// object at offset 8 holds. The class, method and member names are invented; the offset and the
// bytes are the binary's.

extern "C" __declspec(dllimport) int __stdcall SetThreadPriority(void* Thread, int Priority);

struct UnkType_10dbfaf0_Thread
{
    void* unk_0;
};

class UnkType_10dbfaf0
{
public:
    int unk_0;
    int unk_4;
    UnkType_10dbfaf0_Thread* unk_8;
    int unk_c;
    int unk_10;

    void Unk_10dbfaf0(int Priority);
};

// UnkType_10dbfaf0::Unk_10dbfaf0
void UnkType_10dbfaf0::Unk_10dbfaf0(int Priority)
{
    unk_10 = Priority;
    SetThreadPriority(unk_8->unk_0, Priority);
}
