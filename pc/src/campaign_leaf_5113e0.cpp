// campaign_leaf_5113e0.cpp -- one function at file offset 0x5113e0, preferred VA 0x10e113e0. A
// constructor taking a mode: it sets the float at 0x0 to 0.1, the words at 0x4-0x10 to 1000, 10,
// 5 and 5, then for mode 0 sets the float to 0.2 and for mode 1 the float to 0.05 and the word at
// 0x8 to 30. The class, member and parameter names are invented; the offsets, the constants and
// the bytes are the binary's.

class UnkType_10e113e0
{
public:
    UnkType_10e113e0(int Mode);

    float unk_0;
    int unk_4;
    int unk_8;
    int unk_c;
    int unk_10;
};

// UnkType_10e113e0::UnkType_10e113e0
UnkType_10e113e0::UnkType_10e113e0(int Mode)
{
    unk_0 = 0.1f;
    unk_4 = 1000;
    unk_8 = 10;
    unk_c = unk_10 = 5;
    switch ( Mode )
    {
    case 0:
        unk_0 = 0.2f;
        break;
    case 1:
        unk_0 = 0.05f;
        unk_8 = 30;
        break;
    }
}
