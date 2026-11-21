// Work item 0047: Versus RVA 0xc970-0xca74.
// FString / FArray helpers from Unreal Engine 2 (Core/UnTemplate.h).
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;

class FMalloc {
public:
    virtual void* Malloc(DWORD Count, const TCHAR* Tag);
    virtual void* Realloc(void* Original, DWORD Count, const TCHAR* Tag);
    virtual void Free(void* Original);
};
extern FMalloc* GMalloc;

class FString {
public:
    FString(const FString& Other);                  // RVA 0x4640
    ~FString();                                     // RVA 0x48b0
    FString operator+(const TCHAR* Str) const;      // RVA 0x4990
    FString operator+(const FString& Str) const;
    const TCHAR* operator*() const { return ArrayNum ? Data : L""; }
    void Empty();

protected:
    TCHAR* Data;
    INT ArrayNum;
    INT ArrayMax;
};

// RVA 0xca00
FString FString::operator+(const FString& Str) const
{
    return operator+(*Str);
}

// RVA 0xca50: TArray::Empty() with no slack (ArrayMax left untouched).
void FString::Empty()
{
    if (Data)
    {
        GMalloc->Free(Data);
        Data = 0;
    }
    ArrayNum = 0;
}

// RVA 0xc9d0: alphanumeric test; the character arrives in AX
// (link-time custom calling convention).
static __declspec(noinline) INT appIsAlnum(TCHAR c)
{
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9');
}

INT CallIsAlnum(TCHAR c) { return appIsAlnum(c); }

// RVA 0xc970: default initializer for a 0x40-byte record with a vtable
// (vtable at 0x10c0d9a0; class unidentified, hence the neutral name). The
// object arrives in EAX (link-time custom calling convention).
extern const void* const vtable_UnnamedClass_c970[];

struct UnnamedClass_c970 {
    const void* const* Methods;
    INT Field04;
    INT Field08;
    INT Field0C;
    INT Field10;
    INT Field14;
    INT Field18;
    INT Field1C;
    INT Field20;
    INT Field24;
    INT Field28;
    INT Field2C;
    INT Field30;
    INT Field34;
    INT Field38;
    INT Field3C;
};

static __declspec(noinline) void InitUnnamedClass_c970(UnnamedClass_c970* Obj)
{
    Obj->Field04 = 0xaf;
    Obj->Field08 = 2000;
    Obj->Field0C = 0;
    Obj->Field10 = 0;
    Obj->Field18 = 0;
    Obj->Field1C = 0;
    Obj->Field20 = 1;
    Obj->Field24 = 1;
    Obj->Field28 = 1;
    Obj->Field2C = 0;
    Obj->Field30 = 0;
    Obj->Field34 = 3;
    Obj->Field38 = 0;
    Obj->Field3C = -1;
    Obj->Methods = vtable_UnnamedClass_c970;
    Obj->Field14 = 1;
}

void CallInitUnnamedClass_c970(UnnamedClass_c970* Obj) { InitUnnamedClass_c970(Obj); }
