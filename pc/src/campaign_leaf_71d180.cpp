// campaign_leaf_71d180.cpp -- one function at file offset 0x71d180, preferred VA 0x1101d180. A
// constructor: it runs the base constructor at VA 0x10e68230 and zeroes the words from 0x2c down
// to 0x20 and from 0x3c down to 0x30. The class names are invented; the offsets and the callee's
// address are the binary's.

class UnkType_1101d180_Base
{
public:
    UnkType_1101d180_Base();

    unsigned char unk_0[0x20];
};

class UnkType_1101d180 : public UnkType_1101d180_Base
{
public:
    UnkType_1101d180();

    int unk_20;
    int unk_24;
    int unk_28;
    int unk_2c;
    int unk_30;
    int unk_34;
    int unk_38;
    int unk_3c;
};

// UnkType_1101d180::UnkType_1101d180
UnkType_1101d180::UnkType_1101d180()
{
    unk_2c = 0;
    unk_28 = 0;
    unk_24 = 0;
    unk_20 = 0;
    unk_3c = 0;
    unk_38 = 0;
    unk_34 = 0;
    unk_30 = 0;
}
