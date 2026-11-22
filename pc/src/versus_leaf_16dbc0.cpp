// versus_leaf_16dbc0.cpp -- returns the int member at 0x80 of the object, from the
// function at file offset 0x16dbc0 (VA 0x10a6dbc0). The class and method names are invented; the
// offset and the no-argument return are the binary's.

class UnkType_10a6dbc0
{
public:
    int GetUnk80();

private:
    unsigned char unk_00[0x80];  // not read by this function
    int unk_80;                  // read by GetUnk80
};

// UnkType_10a6dbc0::GetUnk80
int UnkType_10a6dbc0::GetUnk80()
{
    return unk_80;
}
