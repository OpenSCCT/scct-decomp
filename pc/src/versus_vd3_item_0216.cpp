// Item 0216: RVA 0x54350, reflected vtable slot 36 of UBoolProperty/UStrProperty/
// UStructProperty. Copies every array element by calling the per-element copy
// virtual (slot 35, CopySingleValue). In this build ArrayDim and ElementSize
// are 16-bit fields at 0x30/0x32.
typedef unsigned char BYTE;
typedef int INT;
typedef short SWORD;
class UObject;

class UProperty
{
public:
    virtual void VSlot0(); virtual void VSlot1(); virtual void VSlot2(); virtual void VSlot3();
    virtual void VSlot4(); virtual void VSlot5(); virtual void VSlot6(); virtual void VSlot7();
    virtual void VSlot8(); virtual void VSlot9(); virtual void VSlot10(); virtual void VSlot11();
    virtual void VSlot12(); virtual void VSlot13(); virtual void VSlot14(); virtual void VSlot15();
    virtual void VSlot16(); virtual void VSlot17(); virtual void VSlot18(); virtual void VSlot19();
    virtual void VSlot20(); virtual void VSlot21(); virtual void VSlot22(); virtual void VSlot23();
    virtual void VSlot24(); virtual void VSlot25(); virtual void VSlot26(); virtual void VSlot27();
    virtual void VSlot28(); virtual void VSlot29(); virtual void VSlot30(); virtual void VSlot31();
    virtual void VSlot32(); virtual void VSlot33(); virtual void VSlot34();
    virtual void CopySingleValue(void *Dest, void *Src, UObject *SuperObject);
    virtual void CopyCompleteValue(void *Dest, void *Src, UObject *SuperObject);

    BYTE Pad04[0x2C];
    SWORD ArrayDim;     // 0x30
    SWORD ElementSize;  // 0x32
};

void UProperty::CopyCompleteValue(void *Dest, void *Src, UObject *SuperObject)
{
    for (INT i = 0; i < ArrayDim; i++)
        CopySingleValue((BYTE *)Dest + i * ElementSize, (BYTE *)Src + i * ElementSize, SuperObject);
}
