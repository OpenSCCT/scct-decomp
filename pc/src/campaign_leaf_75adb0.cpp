// campaign_leaf_75adb0.cpp -- one function at file offset 0x75adb0, preferred VA 0x1105adb0. It
// returns 0 when the word at 0x0 is set. Otherwise, for the values 0x14 and 0x15 of the word at 0x4
// it sets the word at 0x0 to 1 and returns 2 or 3; for any other value it returns 1. The class,
// method and member names are invented; the offset and the bytes are the binary's.

class UnkType_1105adb0
{
public:
    int Unk_1105adb0();

    int unk_0;
    int unk_4;
};

// UnkType_1105adb0::Unk_1105adb0
int UnkType_1105adb0::Unk_1105adb0()
{
    if ( unk_0 != 0 )
    {
        return 0;
    }
    switch ( unk_4 )
    {
    case 0x14:
        unk_0 = 1;
        return 2;
    case 0x15:
        unk_0 = 1;
        return 3;
    }
    return 1;
}
