// campaign_leaf_2bc060.cpp -- a member function at VA 0x10bbc060 that calls the member at VA
// 0x1098dc80, passes this to the member at VA 0x10bd87c0 of the object the pointer at 0x424 refers
// to, and calls the member at VA 0x10bbc020. The class, method and member names are invented; the
// offsets and addresses are the binary's.

class UnkType_10bbc060;

class UnkType_10bd87c0
{
public:
    void Unk_10bd87c0(UnkType_10bbc060* Owner);
};

class UnkType_10bbc060
{
public:
    void Unk_1098dc80();
    void Unk_10bbc020();
    void Unk_10bbc060();

private:
    unsigned char unk_000[0x424];
    UnkType_10bd87c0* unk_424;
};

// UnkType_10bbc060::Unk_10bbc060
void UnkType_10bbc060::Unk_10bbc060()
{
    Unk_1098dc80();
    unk_424->Unk_10bd87c0(this);
    Unk_10bbc020();
}
