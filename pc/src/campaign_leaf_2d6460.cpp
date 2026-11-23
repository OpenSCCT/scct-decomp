// campaign_leaf_2d6460.cpp -- method at VA 0x10bd6460 taking a name: passes it to the method at VA
// 0x1098fde0, makes a function-local static name L"BBRoom" on first use (through the name
// constructor at VA 0x10cd4790 with 2), and calls the method at VA 0x10bd5e90 when the argument
// equals it. The class, member and method names are invented; the string and the addresses are the
// binary's.

class UnkType_10bd6460_Name
{
public:
    UnkType_10bd6460_Name(const unsigned short* Text, int FindType);

    int operator==(const UnkType_10bd6460_Name& Other) const
    {
        return unk_00 == Other.unk_00;
    }

private:
    int unk_00;
};

class UnkType_10bd6460
{
public:
    void Unk_10bd6460(UnkType_10bd6460_Name Name);
    void Unk_1098fde0(UnkType_10bd6460_Name Name);
    void Unk_10bd5e90();
};

// UnkType_10bd6460::Unk_10bd6460
void UnkType_10bd6460::Unk_10bd6460(UnkType_10bd6460_Name Name)
{
    Unk_1098fde0(Name);
    static UnkType_10bd6460_Name Room(L"BBRoom", 2);
    if ( Name == Room )
    {
        Unk_10bd5e90();
    }
}
