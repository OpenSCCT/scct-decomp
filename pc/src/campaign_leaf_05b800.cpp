// campaign_leaf_05b800.cpp -- free function at VA 0x1095b800: constructs a local object from its
// argument with the constructor at VA 0x10d7cf00, passes it to the free function at VA 0x10d7db50,
// destroys it with the destructor at VA 0x10d7cf40 and returns 1. The class and function names are
// invented; the addresses are the binary's.

class UnkType_10d7cf00_05b800
{
public:
    UnkType_10d7cf00_05b800(int Value);
    ~UnkType_10d7cf00_05b800();

private:
    int unk_00;
};

void Unk_10d7db50(UnkType_10d7cf00_05b800& Value);

// Unk_1095b800
int Unk_1095b800(int Value)
{
    UnkType_10d7cf00_05b800 Local(Value);
    Unk_10d7db50(Local);
    return 1;
}
