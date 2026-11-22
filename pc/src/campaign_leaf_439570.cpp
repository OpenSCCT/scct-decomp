// campaign_leaf_439570.cpp -- free function at VA 0x10d39570: deletes the object the global at
// VA 0x11317d30 points to through its virtual destructor and clears the global. All names are
// invented.

class UnkType_11317d30
{
public:
    virtual ~UnkType_11317d30();
};

extern UnkType_11317d30* GUnk_11317d30;

// Unk_10d39570
void Unk_10d39570()
{
    delete GUnk_11317d30;
    GUnk_11317d30 = 0;
}
