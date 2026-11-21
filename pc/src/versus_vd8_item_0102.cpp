/* w4_item_0102.cpp -- Versus work item 0102 (RVA 0x150910) */

// Neutral names: class identities for vtables 0x303320 and 0x30330c are not yet recovered.

class OwnedObject_150910
{
public:
    virtual ~OwnedObject_150910();
};

class BaseClass_150910
{
public:
    virtual ~BaseClass_150910() {}
};

class UnnamedClass_150910 : public BaseClass_150910
{
public:
    OwnedObject_150910 *Child;

    virtual ~UnnamedClass_150910();
};

/* UnnamedClass_150910::~UnnamedClass_150910 (RVA 0x150910) */
UnnamedClass_150910::~UnnamedClass_150910()
{
    delete Child;
    Child = 0;
}
