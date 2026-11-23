// campaign_leaf_48f670.cpp -- thiscall method at VA 0x10d8f670. It passes the given stream and the
// addresses of the words at 0x00-0x10 to the function at 0x10da4570, then the addresses of the
// words at 0x14-0x20 to the stream's method at 0x10d9df90. The class, method and parameter names
// are invented.

class UnkType_10d8f670_Stream
{
public:
    void Unk_10d9df90(int* Value);
};

void Unk_10da4570(UnkType_10d8f670_Stream* Stream, int* Value);

class UnkType_10d8f670
{
public:
    void Unk_10d8f670(UnkType_10d8f670_Stream* Stream);

private:
    int unk_0;
    int unk_4;
    int unk_8;
    int unk_c;
    int unk_10;
    int unk_14;
    int unk_18;
    int unk_1c;
    int unk_20;
};

// UnkType_10d8f670::Unk_10d8f670
void UnkType_10d8f670::Unk_10d8f670(UnkType_10d8f670_Stream* Stream)
{
    Unk_10da4570(Stream, &unk_0);
    Unk_10da4570(Stream, &unk_4);
    Unk_10da4570(Stream, &unk_8);
    Unk_10da4570(Stream, &unk_c);
    Unk_10da4570(Stream, &unk_10);
    Stream->Unk_10d9df90(&unk_14);
    Stream->Unk_10d9df90(&unk_18);
    Stream->Unk_10d9df90(&unk_1c);
    Stream->Unk_10d9df90(&unk_20);
}
