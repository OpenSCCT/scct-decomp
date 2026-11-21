// Work item 0111: Versus RVA 0x1526c0-0x152734, 2 functions, 103 bytes.
// Neutral class and member names (original class not yet identified in retail).

typedef unsigned char BYTE;
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;

class UObject;
class FName;

class FMalloc
{
public:
    virtual void* Malloc(DWORD Count, const TCHAR* Tag);
    virtual void* Realloc(void* Original, DWORD Count, const TCHAR* Tag);
    virtual void Free(void* Original);
};

extern FMalloc* GMalloc;

class FArchive
{
public:
    virtual ~FArchive();
    virtual void Serialize(void* V, INT Length);
    virtual void SerializeBits(void* V, INT LengthBits);
    virtual void SerializeInt(DWORD& Value, DWORD Max);
    virtual void Preload(void* Object);
    virtual void CountBytes(DWORD InNum, DWORD InMax);
    virtual FArchive& operator<<(FName& N);
    virtual FArchive& operator<<(UObject*& Res);

    INT ArVer;
    INT ArNetVer;
    INT ArLicenseeVer;
    UBOOL ArIsLoading;
    UBOOL ArIsSaving;

    UBOOL IsLoading() const { return ArIsLoading; }
    UBOOL IsSaving() const { return ArIsSaving; }
};

class UBaseObject
{
public:
    virtual ~UBaseObject();
};

class UObjectTable : public UBaseObject
{
public:
    BYTE unk_4[0x470 - 4];
    BYTE ItemCount;         // 0x470
    BYTE unk_471[0x478 - 0x471];
    UObject** Items;        // 0x478

    virtual ~UObjectTable();
    void SerializeItems(FArchive& Ar);
};

// RVA 0x1526c0
UObjectTable::~UObjectTable()
{
    GMalloc->Free(Items);
}

// RVA 0x1526f0
void UObjectTable::SerializeItems(FArchive& Ar)
{
    for (INT i = 0; i < ItemCount; i++)
    {
        if (!Ar.IsLoading() && !Ar.IsSaving() && Items[i])
            Ar << Items[i];
    }
}

// Scaffolding for the link, not part of the unit.
extern void ExternalBarrier(UObjectTable* Obj, FArchive* Ar);
void Driver_1526f0(UObjectTable* Obj, FArchive* Ar)
{
    ExternalBarrier(Obj, Ar);
    Obj->SerializeItems(*Ar);
    ExternalBarrier(Obj, Ar);
    Obj->SerializeItems(*Ar);
}
