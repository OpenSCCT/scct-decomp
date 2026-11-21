// FArray::Empty (Unreal Engine 2), RVA 0x4550.
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;

class FMalloc
{
public:
    virtual void* Malloc(DWORD Count, const TCHAR* Tag);
    virtual void* Realloc(void* Original, DWORD Count, const TCHAR* Tag);
    virtual void Free(void* Original);
};

extern FMalloc* GMalloc;

class FArray
{
public:
    void Empty(INT ElementSize, INT Slack);
protected:
    void* Data;
    INT ArrayNum;
    INT ArrayMax;
};

void FArray::Empty(INT ElementSize, INT Slack)
{
    ArrayNum = 0;
    if (Slack)
    {
        if (ArrayMax != Slack)
        {
            ArrayMax = Slack;
            if (!Data)
                Data = GMalloc->Malloc(ElementSize * Slack, L"FArray::Empty");
            else
                Data = GMalloc->Realloc(Data, ElementSize * Slack, L"FArray");
        }
    }
    else if (Data)
    {
        GMalloc->Free(Data);
        Data = 0;
        ArrayMax = 0;
    }
}
