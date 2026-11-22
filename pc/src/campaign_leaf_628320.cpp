// campaign_leaf_628320.cpp -- stdcall function at VA 0x10f28320: when the object is not null, passes
// the second argument to the method at VA 0x10f2bea0 on it and returns true; otherwise false. All
// names are invented.

class UnkType_10f2bea0
{
public:
    void Unk_10f2bea0(int Value);
};

// Unk_10f28320
bool __stdcall Unk_10f28320(UnkType_10f2bea0* Object, int Value)
{
    if ( Object )
    {
        Object->Unk_10f2bea0(Value);
        return true;
    }
    return false;
}
