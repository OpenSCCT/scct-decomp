// versus_leaf_23a040.cpp -- stores its second argument in the int at 0 of the object; the first argument is never read, at file offset 0x23a040 (VA 0x10b3a040).
// The class, member and method names are invented; the offsets and the argument sizes
// are the binary's.

class UnkType_10b3a040
{
public:
    UnkType_10b3a040 &SetUnk00(int Unused, int Value);

private:
    int unk_00;                         // written by SetUnk00
};

// UnkType_10b3a040::SetUnk00
// Unused is never read; the function pops both arguments (ret 8).
UnkType_10b3a040 &UnkType_10b3a040::SetUnk00(int Unused, int Value)
{
    unk_00 = Value;
    return *this;
}
