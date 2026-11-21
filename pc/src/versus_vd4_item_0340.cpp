// Item 0340: RVA 0x92f70, an LTCG-compiled helper. The linker gave it a custom
// convention: the object in ECX, two values in ESI/EDI, the target pointer on
// the stack with the caller cleaning up (a __cdecl function). Names are
// neutral: there is no evidence for the class.
typedef unsigned long DWORD;
typedef DWORD UBOOL;

struct UnnamedTarget_92f70
{
    char Pad[0x7e];
    unsigned char bFlag;                    // +0x7e
};

class UnnamedClass_92f70
{
public:
    virtual void V00(); virtual void V04(); virtual void V08(); virtual void V0C();
    virtual void V10(); virtual void V14(); virtual void V18(); virtual void V1C();
    virtual void V20(); virtual void V24(); virtual void V28(); virtual void V2C();
    virtual void V30(); virtual void V34(); virtual void V38(); virtual void V3C();
    virtual void V40(); virtual void V44(); virtual void V48(); virtual void V4C();
    virtual void V50(); virtual void V54();
    virtual UBOOL V58(void *A);             // vtable slot 22
};

bool Check_92f70(UnnamedClass_92f70 *Obj, void *A, void *B, UnnamedTarget_92f70 *Target)
{
    if (Obj->V58(A))
        return A != B;
    Target->bFlag = 1;
    return B != 0;
}

// Scaffolding for the link, not part of the unit. Built with /Ob1 so the
// driver calls the helper instead of inlining it, as retail callers do.
void Sink(int);
void Driver_92f70(UnnamedClass_92f70 **O, UnnamedTarget_92f70 **T, void **A, void **B)
{
    Sink(Check_92f70(O[0], A[0], B[0], T[0]));
    Sink(Check_92f70(O[1], A[1], B[1], T[1]));
    Sink(Check_92f70(O[2], A[2], B[2], T[2]));
    Sink(Check_92f70(O[3], A[3], B[3], T[3]));
    Sink(Check_92f70(O[4], A[4], B[4], T[4]));
    Sink(Check_92f70(O[5], A[5], B[5], T[5]));
    Sink(Check_92f70(O[6], A[6], B[6], T[6]));
    Sink(Check_92f70(O[7], A[7], B[7], T[7]));
    Sink(Check_92f70(O[8], A[8], B[8], T[8]));
    Sink(Check_92f70(O[9], A[9], B[9], T[9]));
    Sink(Check_92f70(O[10], A[10], B[10], T[10]));
    Sink(Check_92f70(O[11], A[11], B[11], T[11]));
}
