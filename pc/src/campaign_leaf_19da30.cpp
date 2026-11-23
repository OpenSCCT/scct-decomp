// campaign_leaf_19da30.cpp -- one function at file offset 0x19da30, preferred VA 0x10a9da30.
// For every index from its second argument to its third it reads two integers through its first
// argument's method at VA 0x10d9df90, the first preset to -1, and passes the argument, the first
// integer and the index to its own method at VA 0x10b00fa0. The class, method and member names are
// invented; the offset and the bytes are the binary's.

class UnkType_10a9da30_Reader
{
public:
    void Unk_10d9df90(int* Value);
};

class UnkType_10a9da30
{
public:
    void Unk_10b00fa0(UnkType_10a9da30_Reader* Reader, int Value, unsigned int Index);
    void Unk_10a9da30(UnkType_10a9da30_Reader* Reader, unsigned int First, unsigned int Last);
};

// UnkType_10a9da30::Unk_10a9da30
void UnkType_10a9da30::Unk_10a9da30(UnkType_10a9da30_Reader* Reader, unsigned int First,
    unsigned int Last)
{
    for ( unsigned int i = First; i <= Last; i++ )
    {
        int Value = -1;
        int Other;
        Reader->Unk_10d9df90(&Value);
        Reader->Unk_10d9df90(&Other);
        Unk_10b00fa0(Reader, Value, i);
    }
}
