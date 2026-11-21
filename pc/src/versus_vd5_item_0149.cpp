// Work item 0149: RVA 0xc42e0, an override of UMeshEmitter vtable slot 23
// (calls the base implementation at 0xf9030), then frees two TArrays.
// Class name is neutral: UnnamedEmitter_c42e0 derives from UMeshEmitter.
typedef int INT;

class FMalloc {
public:
    virtual void *Malloc(unsigned long Count, const unsigned short *Tag);
    virtual void *Realloc(void *Original, unsigned long Count, const unsigned short *Tag);
    virtual void Free(void *Original);
};
extern FMalloc *GMalloc;

struct FArray {
    void *Data;
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

class UMeshEmitter {
public:
    void Slot23_f9030();
};

class UnnamedEmitter_c42e0 : public UMeshEmitter {
public:
    char Pad[0x3f8];
    FArray ArrayA; // 0x3f8
    FArray ArrayB; // 0x404
    void Slot23_c42e0();
};

void UnnamedEmitter_c42e0::Slot23_c42e0()
{
    UMeshEmitter::Slot23_f9030();
    ArrayA.Empty();
    ArrayB.Empty();
}
