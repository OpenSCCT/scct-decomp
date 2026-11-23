// campaign_leaf_4c6450.cpp -- one function at file offset 0x4c6450, preferred VA 0x10dc6450.
// It fills a local int with the method at 0x10dc5be0 from Value and then passes the address of
// Value and that int to the method at 0x10dc5fd0. The class, method, variable and parameter names
// are invented; the offset and the bytes are the binary's.

class UnkType_10dc6450
{
public:
    void Unk_10dc5be0(int* Out, int* Value);
    void Unk_10dc5fd0(int* Value, int Result);
    void Unk_10dc6450(int Value);
};

// UnkType_10dc6450::Unk_10dc6450
void UnkType_10dc6450::Unk_10dc6450(int Value)
{
    int Result;

    Unk_10dc5be0(&Result, &Value);
    Unk_10dc5fd0(&Value, Result);
}
