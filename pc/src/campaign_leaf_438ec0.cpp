// campaign_leaf_438ec0.cpp -- free function at VA 0x10d38ec0: deletes the object the global at
// VA 0x11317d04 points to through its virtual destructor and clears the global. All names are
// invented.

class UnkType_11317d04
{
public:
    virtual ~UnkType_11317d04();
};

extern UnkType_11317d04* GUnk_11317d04;

// Unk_10d38ec0
void Unk_10d38ec0()
{
    delete GUnk_11317d04;
    GUnk_11317d04 = 0;
}
