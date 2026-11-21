// Work item 0107: RVA 0xb0900.
typedef unsigned long DWORD;
typedef int INT;
typedef unsigned short TCHAR;

class FMalloc
{
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag);
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag);
    virtual void Free(void *Original);
};
extern FMalloc *GMalloc;

template <class T> class TArray
{
public:
    T *Data;
    INT ArrayNum;
    INT ArrayMax;
    void Empty()
    {
        ArrayNum = 0;
        if (Data) {
            GMalloc->Free(Data);
            Data = 0;
            ArrayMax = 0;
        }
    }
};

// UMeshEmitter vtable slot 23 (0x9f9030); name of the slot not recovered.
class UMeshEmitter
{
public:
    virtual void VSlot0();
    void Slot23_9f9030();
    char Pad[0x4c8];
};

// Derived class name not recovered; neutral name from the RVA.
class UnnamedEmitter_b0900 : public UMeshEmitter
{
public:
    TArray<INT> ArrayA; // 0x4cc
    TArray<INT> ArrayB; // 0x4d8
    void Slot23_b0900();
};

void UnnamedEmitter_b0900::Slot23_b0900()
{
    ArrayA.Empty();
    ArrayB.Empty();
    UMeshEmitter::Slot23_9f9030();
}
