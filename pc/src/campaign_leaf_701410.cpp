// campaign_leaf_701410.cpp -- one function at file offset 0x701410, preferred VA 0x11001410. A
// constructor taking one value: it runs the base constructor at VA 0x10fff1e0 with that value and
// installs the vtable at VA 0x11170738. The class names are invented; the offset and the
// addresses are the binary's.

class UnkType_10fff1e0
{
public:
    UnkType_10fff1e0(int Value);
    virtual ~UnkType_10fff1e0();
};

class UnkType_11001410 : public UnkType_10fff1e0
{
public:
    UnkType_11001410(int Value);
    virtual ~UnkType_11001410();
};

// UnkType_11001410::UnkType_11001410
UnkType_11001410::UnkType_11001410(int Value)
    : UnkType_10fff1e0(Value)
{
}
