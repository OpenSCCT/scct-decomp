#ifndef VERSUS_PROPERTY_H
#define VERSUS_PROPERTY_H

class UPackageMap;
class FArchive;

enum ECppProperty { EC_CppProperty };

class UProperty : public UField {
public:
    virtual ~UProperty();
    virtual void CleanupDestroyed(BYTE *Data);
    virtual INT Link(FArchive &Ar, UProperty *Prev);
    virtual UBOOL Identical(const void *A, const void *B) const;
    virtual void SerializeItem(FArchive &Ar, void *Value, INT MaxReadBytes) const;
    virtual UBOOL NetSerializeItem(FArchive &Ar, UPackageMap *Map, void *Data) const;
    virtual void ExportTextItem(TCHAR *Text, BYTE *Value, BYTE *Default, INT PortFlags) const;
    virtual const TCHAR *ImportText(const TCHAR *Buffer, BYTE *Data, INT PortFlags) const;
    virtual void VirtualSlot34();
    virtual void CopySingleValue(void *Dest, void *Src, UObject *SuperObject);
    virtual void CopyCompleteValue(void *Dest, void *Src, UObject *SuperObject);
    virtual void DestroyValue(void *Dest);
    virtual void VirtualSlot38();
    virtual void VirtualSlot39();

    short ArrayDim;
    short ElementSize;
    DWORD PropertyFlags;
    FName Category;
    INT Offset;
    BYTE unk_40[8];
    UProperty *ConstructorLinkNext;
    UProperty *NextRef;
    BYTE unk_50[6];
    _WORD RepIndex;

    UBOOL Matches(const void *A, const void *B, INT ArrayIndex) const
    {
        INT FieldOffset = Offset + ArrayIndex * ElementSize;
        return Identical((const BYTE *)A + FieldOffset, B ? (const BYTE *)B + FieldOffset : 0);
    }
    static UClass PrivateStaticClass;
    static UClass *StaticClass() { return &PrivateStaticClass; }
    UProperty();
    UProperty(ECppProperty, INT InOffset, FName InCategory, DWORD InFlags);
};

#endif
