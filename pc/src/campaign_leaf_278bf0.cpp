// campaign_leaf_278bf0.cpp -- destructor at VA 0x10b78bf0 of a class with three base classes, at 0x00,
// 0x08 and 0x10 (vtables VA 0x110e7658, 0x110e7624 and 0x110e761c): calls the method at VA
// 0x10b78ae0, destroys the member at 0x38 (destructor at VA 0x1090ba70), then the base classes in
// reverse order. The bases at 0x08 and 0x00 (vtables VA 0x110dfbe4 and 0x110dfc18) each release a
// counted object held at their 0x04: the count at the object's 0x04 is decremented, or the object
// is deleted through its virtual destructor when the count is 1 or less. The class, member and
// method names are invented; the offsets and the addresses are the binary's.

class UnkType_10b78bf0_Counted
{
public:
    virtual ~UnkType_10b78bf0_Counted();

    unsigned int unk_04;
};

class UnkType_10b78bf0_Handle
{
public:
    ~UnkType_10b78bf0_Handle()
    {
        if ( unk_00 )
        {
            unsigned int Count = unk_00->unk_04;
            if ( Count <= 1 )
            {
                delete unk_00;
            }
            else
            {
                unk_00->unk_04 = Count - 1;
            }
        }
    }

private:
    UnkType_10b78bf0_Counted* unk_00;
};

class UnkType_10b78bf0_Base00
{
public:
    virtual ~UnkType_10b78bf0_Base00()
    {
    }

private:
    UnkType_10b78bf0_Handle unk_04;
};

class UnkType_10b78bf0_Base08
{
public:
    virtual ~UnkType_10b78bf0_Base08()
    {
    }

private:
    UnkType_10b78bf0_Handle unk_04;
};

class UnkType_10b78bf0_Base10
{
public:
    virtual ~UnkType_10b78bf0_Base10()
    {
    }

private:
    unsigned char unk_04[0x38 - 0x14];
};

class UnkType_10b78bf0_38
{
public:
    ~UnkType_10b78bf0_38();

private:
    int unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_10b78bf0 : public UnkType_10b78bf0_Base00,
                         public UnkType_10b78bf0_Base08,
                         public UnkType_10b78bf0_Base10
{
public:
    virtual ~UnkType_10b78bf0();

    void Unk_10b78ae0();

private:
    UnkType_10b78bf0_38 unk_38;
};

// UnkType_10b78bf0::~UnkType_10b78bf0
UnkType_10b78bf0::~UnkType_10b78bf0()
{
    Unk_10b78ae0();
}
