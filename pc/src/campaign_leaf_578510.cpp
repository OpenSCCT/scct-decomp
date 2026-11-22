// campaign_leaf_578510.cpp -- thiscall method at VA 0x10e78510: when the byte at 0x14 is set and
// its argument is not null, passes the argument to the cdecl function at VA 0x10e77230. The class
// and method names are invented.

void Unk_10e77230(void* Pointer);

class UnkType_10e78510
{
public:
    void Unk_10e78510(void* Pointer);

private:
    int unk_00[5];
    unsigned char unk_14;
};

// UnkType_10e78510::Unk_10e78510
void UnkType_10e78510::Unk_10e78510(void* Pointer)
{
    if ( unk_14 && Pointer )
    {
        Unk_10e77230(Pointer);
    }
}
