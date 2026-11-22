// campaign_leaf_5fb7a0.cpp -- constructor at VA 0x10efb7a0: stores the result of the stdcall
// function at VA 0x10efb890 for its first argument at 0x00 and its second argument at 0x04. guess:
// an IPv4 address (VA 0x10efb890 wraps inet_addr) and a port. The class and function names are
// invented.

unsigned long __stdcall Unk_10efb890(const char* Address);

class UnkType_10efb7a0
{
public:
    UnkType_10efb7a0(const char* Address, int Value);

private:
    unsigned long unk_00;
    int unk_04;
};

// UnkType_10efb7a0::UnkType_10efb7a0
UnkType_10efb7a0::UnkType_10efb7a0(const char* Address, int Value)
{
    unk_00 = Unk_10efb890(Address);
    unk_04 = Value;
}
