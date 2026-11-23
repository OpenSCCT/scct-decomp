// campaign_leaf_0a6150.cpp -- method at VA 0x109a6150: if the pointer at 0x2b4 is set, calls the
// method at VA 0x10a562d0 on the object it points to with this object and its argument. The class,
// member and method names are invented; the offsets and the address are the binary's.

class UnkType_109a6150;

class UnkType_109a6150_10a562d0
{
public:
    void Unk_10a562d0(UnkType_109a6150* Owner, int Value);
};

class UnkType_109a6150
{
public:
    void Unk_109a6150(int Value);

private:
    unsigned char unk_000[0x2b4];
    UnkType_109a6150_10a562d0* unk_2b4;
};

// UnkType_109a6150::Unk_109a6150
void UnkType_109a6150::Unk_109a6150(int Value)
{
    if ( unk_2b4 )
    {
        unk_2b4->Unk_10a562d0(this, Value);
    }
}
