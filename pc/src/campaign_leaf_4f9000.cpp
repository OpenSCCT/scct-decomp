// campaign_leaf_4f9000.cpp -- method at VA 0x10df9000: for each of the flags 1, 2 and 4 that is
// set, reads a value from its first argument (methods at VA 0x10d9dd50 and 0x10d9df90) and passes
// it with its last argument to the methods at VA 0x10df8e00, 0x10df8c00 and 0x10df8cf0. The class,
// method and parameter names are invented; the flags and the addresses are the binary's.

class UnkType_10df9000_Reader
{
public:
    void Unk_10d9dd50(int* Value);
    void Unk_10d9df90(int* Value);
};

class UnkType_10df9000
{
public:
    void Unk_10df9000(UnkType_10df9000_Reader* Reader, unsigned char Flags, int Arg);
    void Unk_10df8e00(int* Value, int Arg);
    void Unk_10df8c00(int* Value, int Arg);
    void Unk_10df8cf0(int* Value, int Arg);
};

// UnkType_10df9000::Unk_10df9000
void UnkType_10df9000::Unk_10df9000(UnkType_10df9000_Reader* Reader, unsigned char Flags, int Arg)
{
    if ( Flags & 1 )
    {
        int Value;
        Reader->Unk_10d9dd50(&Value);
        Unk_10df8e00(&Value, Arg);
    }
    if ( Flags & 2 )
    {
        int Value;
        Reader->Unk_10d9dd50(&Value);
        Unk_10df8c00(&Value, Arg);
    }
    if ( Flags & 4 )
    {
        int Value;
        Reader->Unk_10d9df90(&Value);
        Unk_10df8cf0(&Value, Arg);
    }
}
