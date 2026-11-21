// Work item 0219: UDelegateProperty virtuals (RVA 0x54940-0x54c58).
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef unsigned char BYTE;
typedef short SWORD;

class UObject;
class UPackageMap;

struct FNameEntry
{
    BYTE Pad[0xc];
    TCHAR Name[1];
};
extern FNameEntry **GNames_Data;     // FName::Names.Data

struct FName
{
    INT Index;
    const TCHAR *operator*() const { return GNames_Data[Index]->Name; }
};

class FArchive
{
public:
    virtual ~FArchive();
    virtual void V01(); virtual void V02(); virtual void V03(); virtual void V04();
    virtual void V05();
    // MSVC lays out overloaded virtuals in reverse declaration order.
    virtual FArchive &operator<<(FName &N);        // +0x1c (slot after UObject*&)
    virtual FArchive &operator<<(UObject *&Res);   // +0x18
};

class UObject
{
public:
    virtual ~UObject();
    virtual void V01(); virtual void V02(); virtual void V03(); virtual void V04();
    virtual void V05(); virtual void V06(); virtual void V07(); virtual void V08();
    virtual void V09(); virtual void V10();
    virtual UBOOL IsPendingKill();                 // +0x2c
    INT Index;
    UObject *HashNext;
    void *StateFrame;
    void *_Linker;
    INT _LinkerIndex;
    UObject *Outer;
    DWORD ObjectFlags;
    FName Name;
    const TCHAR *GetName() const { return *Name; }
};

struct FScriptDelegate
{
    UObject *Object;
    FName FunctionName;
};

int appSprintf(TCHAR *Dest, const TCHAR *Fmt, ...);
extern const TCHAR DelegateExportFmt[]; // "%s.%s"

class UDelegateProperty
{
public:
    virtual ~UDelegateProperty();
    BYTE Pad[0x30 - 4];
    SWORD ArrayDim;      // 0x30
    SWORD ElementSize;   // 0x32

    void CleanupDestroyed(BYTE *Data);
    UBOOL Identical(const void *A, const void *B) const;
    void SerializeItem(FArchive &Ar, void *Value, INT MaxReadBytes) const;
    UBOOL NetSerializeItem(FArchive &Ar, UPackageMap *Map, void *Data) const;
    void ExportTextItem(TCHAR *ValueStr, BYTE *PropertyValue, BYTE *DefaultValue, INT PortFlags) const;
};

void UDelegateProperty::CleanupDestroyed(BYTE *Data)
{
    for (INT i = 0; i < ArrayDim; i++)
    {
        FScriptDelegate *D = (FScriptDelegate *)(Data + i * ElementSize);
        if (D->Object && D->Object->IsPendingKill())
        {
            D->Object = 0;
            D->FunctionName.Index = 0;
        }
    }
}

UBOOL UDelegateProperty::Identical(const void *A, const void *B) const
{
    FScriptDelegate *DA = (FScriptDelegate *)A;
    FScriptDelegate *DB = (FScriptDelegate *)B;
    if (!B)
        return DA->Object == 0;
    return DA->Object == DB->Object && DA->FunctionName.Index == DB->FunctionName.Index;
}

void UDelegateProperty::SerializeItem(FArchive &Ar, void *Value, INT MaxReadBytes) const
{
    Ar << ((FScriptDelegate *)Value)->Object << ((FScriptDelegate *)Value)->FunctionName;
}

UBOOL UDelegateProperty::NetSerializeItem(FArchive &Ar, UPackageMap *Map, void *Data) const
{
    Ar << ((FScriptDelegate *)Data)->Object << ((FScriptDelegate *)Data)->FunctionName;
    return 1;
}

void UDelegateProperty::ExportTextItem(TCHAR *ValueStr, BYTE *PropertyValue, BYTE *DefaultValue, INT PortFlags) const
{
    FScriptDelegate *D = (FScriptDelegate *)PropertyValue;
    appSprintf(ValueStr, DelegateExportFmt, D->Object->GetName(), *D->FunctionName);
}
