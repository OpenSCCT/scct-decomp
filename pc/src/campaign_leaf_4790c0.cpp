// campaign_leaf_4790c0.cpp -- constructor at VA 0x10d790c0: runs the base constructor at
// VA 0x10d78e00, then constructs the member at offset 8 with the constructor at VA 0x10d79b20.
// All names are invented.

class UnkType_10d78e00
{
public:
    UnkType_10d78e00();

private:
    int unk_00;
    int unk_04;
};

class UnkType_10d79b20
{
public:
    UnkType_10d79b20();

private:
    int unk_00;
};

class UnkType_10d790c0 : public UnkType_10d78e00
{
public:
    UnkType_10d790c0();

private:
    UnkType_10d79b20 unk_08;
};

// UnkType_10d790c0::UnkType_10d790c0
UnkType_10d790c0::UnkType_10d790c0()
{
}
