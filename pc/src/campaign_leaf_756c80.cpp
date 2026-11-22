// campaign_leaf_756c80.cpp -- one function at file offset 0x756c80, preferred VA 0x11056c80. For
// the argument 1 it sets the words at 0x94 and 0x98 to 1 and 0 and returns 1; for 3 it sets them to
// 3 and 2 and returns 1; for any other value it sets them to 1 and 0 and returns 0. The class,
// method and member names are invented; the offset and the bytes are the binary's.

class UnkType_11056c80
{
public:
    int Unk_11056c80(int Value);

    unsigned char unk_0[0x94];
    int unk_94;
    int unk_98;
};

// UnkType_11056c80::Unk_11056c80
int UnkType_11056c80::Unk_11056c80(int Value)
{
    switch ( Value )
    {
    case 1:
        unk_94 = 1;
        unk_98 = 0;
        return 1;
    case 3:
        unk_98 = 2;
        unk_94 = 3;
        return 1;
    }
    unk_94 = 1;
    unk_98 = 0;
    return 0;
}
