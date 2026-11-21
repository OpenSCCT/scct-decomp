// Work item 0224: RVA 0xeef50. Class names are neutral; no vtable label evidence.
typedef int INT;

class UnnamedChild_eef50 {
public:
    virtual void V00(); virtual void V04(); virtual void V08(); virtual void V0C();
    virtual void V10(); virtual void V14(); virtual void V18(); virtual void V1C();
    virtual void V20(); virtual void V24(); virtual void V28(); virtual void V2C();
    virtual void V30(); virtual void V34(); virtual void V38(); virtual void V3C();
    virtual void V40(); virtual void V44(); virtual void V48(); virtual void V4C();
    virtual void V50(); virtual void V54(); virtual void V58(); virtual void V5C();
    virtual void V60(); virtual void V64(); virtual void V68(); virtual void V6C();
    virtual void V70();
    virtual void Update(); // slot 0x74
};

template<class T> struct TArray {
    T *Data;
    INT ArrayNum;
    INT ArrayMax;
    INT Num() const { return ArrayNum; }
    T &operator()(INT i) { return Data[i]; }
};

class UnnamedClass_eef50 {
public:
    char Pad00[0x2c];
    TArray<UnnamedChild_eef50 *> Children; // 0x2c
    UnnamedChild_eef50 *Primary;           // 0x38
    void UpdateAll();
};

void UnnamedClass_eef50::UpdateAll()
{
    if (Primary)
        Primary->Update();
    for (INT i = 0; i < Children.Num(); i++)
        Children(i)->Update();
}
