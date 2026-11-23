// campaign_leaf_05e640.cpp -- constructor at VA 0x1095e640 taking a byte and a value: constructs
// the member at 0x08 with the constructor at VA 0x10d7ce90, stores the byte at 0x00, clears the
// value at 0x04, sets the one at 0x0c to 1 and passes the second argument to the method at VA
// 0x10d7cfe0 of the member at 0x08. The class and member names are invented; the offsets, the
// constant and the addresses are the binary's.

class UnkType_10d7ce90_05e640
{
public:
    UnkType_10d7ce90_05e640();
    void Unk_10d7cfe0(int Value);
};

class UnkType_1095e640
{
public:
    UnkType_1095e640(unsigned char Value, int Arg);

private:
    unsigned char unk_00;
    int unk_04;
    UnkType_10d7ce90_05e640 unk_08;
    int unk_0c;
};

// UnkType_1095e640::UnkType_1095e640
UnkType_1095e640::UnkType_1095e640(unsigned char Value, int Arg)
{
    unk_00 = Value;
    unk_04 = 0;
    unk_0c = 1;
    unk_08.Unk_10d7cfe0(Arg);
}
