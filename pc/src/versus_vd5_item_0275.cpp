// Work item 0275: RVA 0xfc5d0, an LTCG constructor (this on the stack, text in EDX, ret 8).
// Class names are neutral: nothing in the evidence names them. The empty base with a
// destructor supplies the frame state that covers the FString construction.
typedef unsigned short TCHAR;
typedef int INT;
inline void *operator new(unsigned int, void *Mem) { return Mem; }
class FString
{
public:
    TCHAR *Data;
    INT ArrayNum;
    INT ArrayMax;
    FString(const TCHAR *In);
    ~FString();
};
class FName { public: INT Index; };
struct UnnamedBase_fc5d0 { ~UnnamedBase_fc5d0(); };
class UnnamedClass_fc5d0 : public UnnamedBase_fc5d0
{
public:
    virtual ~UnnamedClass_fc5d0();
    FName Name;
    FString Text;
    UnnamedClass_fc5d0(const FName &InName, const TCHAR *InText);
};
UnnamedClass_fc5d0::UnnamedClass_fc5d0(const FName &InName, const TCHAR *InText)
    : Name(InName), Text(InText)
{
}
// Scaffolding for the link, not part of the unit.
void Driver_fc5d0(void *Mem, const FName &N, const TCHAR *T)
{
    new (Mem) UnnamedClass_fc5d0(N, T);
}
