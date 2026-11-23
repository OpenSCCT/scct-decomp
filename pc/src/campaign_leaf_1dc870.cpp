// campaign_leaf_1dc870.cpp -- thiscall method at VA 0x10adc870. Given a key, it finds the first
// object in the pointer array at 0x3c whose word at 0x18 equals the key; when one is found it
// deletes it through its virtual destructor, removes the pointer from the array (method at VA
// 0x10adc520) and returns true; otherwise false. The class, method and member names are invented.

class UnkType_10adc870_Object
{
public:
    virtual ~UnkType_10adc870_Object();

private:
    char unk_04[0x18 - 0x04];

public:
    int unk_18;
};

class UnkType_10adc870_Array
{
public:
    void Unk_10adc520(UnkType_10adc870_Object* const& Item);

    UnkType_10adc870_Object** unk_0;
    int unk_4;
    int unk_8;
};

class UnkType_10adc870
{
public:
    bool Unk_10adc870(int Key);

    // UnkType_10adc870::Find
    UnkType_10adc870_Object* Find(int Key)
    {
        for ( int i = 0; i < unk_3c.unk_4; i++ )
        {
            UnkType_10adc870_Object* Object = unk_3c.unk_0[i];
            if ( Object != 0 && Object->unk_18 == Key )
            {
                return Object;
            }
        }
        return 0;
    }

private:
    char unk_00[0x3c];
    UnkType_10adc870_Array unk_3c;
};

// UnkType_10adc870::Unk_10adc870
bool UnkType_10adc870::Unk_10adc870(int Key)
{
    UnkType_10adc870_Object* Found = Find(Key);
    if ( Found != 0 )
    {
        delete Found;
        unk_3c.Unk_10adc520(Found);
        return true;
    }
    return false;
}
