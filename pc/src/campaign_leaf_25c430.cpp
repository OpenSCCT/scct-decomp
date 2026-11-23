// campaign_leaf_25c430.cpp -- the destructor at VA 0x10b5c430: it installs the class's virtual
// tables at 0x00, 0x08 and 0x10; when the byte at 0x3c is set it clears the two arrays of four ints
// at 0x44 and 0x54 and the ints at 0x68 and 0x6c, calls the member at VA 0x10b64690 and clears the
// byte. It then runs the base destructor at VA 0x10b64760. The class, method and member names are
// invented; the offsets, addresses and slot are the binary's.

class UnkType_10b5c430_Face0
{
public:
    virtual void VirtualSlot0();

private:
    int unk_04;
};

class UnkType_10b5c430_Face8
{
public:
    virtual void VirtualSlot0();

private:
    int unk_04;
};

class UnkType_10b5c430_Face10
{
public:
    virtual void VirtualSlot0();
};

class UnkType_10b5c430_Base : public UnkType_10b5c430_Face0,
                              public UnkType_10b5c430_Face8,
                              public UnkType_10b5c430_Face10
{
public:
    ~UnkType_10b5c430_Base();

    void Unk_10b64690();

private:
    unsigned char unk_14[0x3c - 0x14];

public:
    bool unk_3c;

private:
    unsigned char unk_3d[0x44 - 0x3d];
};

class UnkType_10b5c430 : public UnkType_10b5c430_Base
{
public:
    ~UnkType_10b5c430();

private:
    int unk_44[4];
    int unk_54[4];
    int unk_64;
    int unk_68;
    int unk_6c;
};

// UnkType_10b5c430::~UnkType_10b5c430
UnkType_10b5c430::~UnkType_10b5c430()
{
    if ( unk_3c )
    {
        for ( int i = 0; i < 4; i++ )
        {
            unk_44[i] = 0;
            unk_54[i] = 0;
        }
        unk_68 = 0;
        unk_6c = 0;
        Unk_10b64690();
        unk_3c = false;
    }
}
