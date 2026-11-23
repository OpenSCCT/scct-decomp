// campaign_leaf_19d8d0.cpp -- one function at file offset 0x19d8d0, preferred VA 0x10a9d8d0.
// For every index from its second argument to its third it reads two integers through its first
// argument's method at VA 0x10d9df90, the first preset to -1, and passes the argument, the first
// integer and the index to its own method at VA 0x10b02b60. The class, method and member names are
// invented; the offset and the bytes are the binary's.

class UnkType_10a9d8d0_Reader
{
public:
    void Unk_10d9df90(int* Value);
};

class UnkType_10a9d8d0
{
public:
    void Unk_10b02b60(UnkType_10a9d8d0_Reader* Reader, int Value, unsigned int Index);
    void Unk_10a9d8d0(UnkType_10a9d8d0_Reader* Reader, unsigned int First, unsigned int Last);
};

// UnkType_10a9d8d0::Unk_10a9d8d0
void UnkType_10a9d8d0::Unk_10a9d8d0(UnkType_10a9d8d0_Reader* Reader, unsigned int First,
    unsigned int Last)
{
    for ( unsigned int i = First; i <= Last; i++ )
    {
        int Value = -1;
        int Other;
        Reader->Unk_10d9df90(&Value);
        Reader->Unk_10d9df90(&Other);
        Unk_10b02b60(Reader, Value, i);
    }
}
