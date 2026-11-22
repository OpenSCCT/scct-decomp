// versus_leaf_26a4c0.cpp -- returns the number of shifts that clear the argument, capped at 32, at file offset
// 0x26a4c0 (VA 0x10b6a4c0). The class and method names are invented; the argument size and the __stdcall
// convention are the binary's.

class UnkType_10b6a4c0
{
public:
    static int __stdcall CountUnkShifts(unsigned int Value);
};

// UnkType_10b6a4c0::CountUnkShifts
// The function pops its one argument (ret 4).
int __stdcall UnkType_10b6a4c0::CountUnkShifts(unsigned int Value)
{
    unsigned int Count = 0;
    do
    {
        if (Value == 0)
        {
            break;
        }
        Count++;
        Value >>= 1;
    } while (Count < 0x20);
    return Count;
}
