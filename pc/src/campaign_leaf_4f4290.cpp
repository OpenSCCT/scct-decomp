// campaign_leaf_4f4290.cpp -- empty value destructor at VA 0x10df4290.

class UnkType_10df9e50_Value
{
public:
    ~UnkType_10df9e50_Value();

    UnkType_10df9e50_Value operator=(const UnkType_10df9e50_Value& Other)
    {
        unk_00 = Other.unk_00;
        return *this;
    }

    int unk_00;
};

// UnkType_10df9e50_Value::~UnkType_10df9e50_Value
UnkType_10df9e50_Value::~UnkType_10df9e50_Value()
{
}
