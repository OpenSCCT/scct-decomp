// Work item 0301: RVA 0x104360.
// Unnamed subclass of UMeshEmitter; calls the parent's virtual (slot 23 of
// UMeshEmitter's vtable) and then empties a raw array held at +0x400.
typedef unsigned long DWORD;
typedef int INT;
typedef unsigned short TCHAR;

class FMalloc
{
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag) = 0;
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag) = 0;
    virtual void Free(void *Original) = 0;
};
extern FMalloc *GMalloc;

class UMeshEmitter
{
public:
    void Destroy(); // vtable slot 23, called directly (0x109f9030)
};

class UnnamedClass_104360 : public UMeshEmitter
{
public:
    void Destroy();

    char Pad[0x400];
    void *Data;     // +0x400
    INT ArrayNum;   // +0x404
    INT ArrayMax;   // +0x408
};

void UnnamedClass_104360::Destroy()
{
    UMeshEmitter::Destroy();
    ArrayNum = 0;
    if (Data)
    {
        GMalloc->Free(Data);
        Data = 0;
        ArrayMax = 0;
    }
}
