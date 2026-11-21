// Work item 0381: Versus RVA 0xa52b0-0xa543f.
// Three TArray<T>::~TArray instantiations (element sizes 0x90, 0x3c, 0x30)
// with FArray::~FArray inlined, from a /GL unit (this passed on the stack,
// ret 4). The element types are not recovered: Unnamed_Elem90/3c/30 are
// neutral names for trivially destructible records of those sizes.

typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;

class FMalloc
{
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag) = 0;
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag) = 0;
    virtual void Free(void *Original) = 0;
};
extern FMalloc *GMalloc;

class FArray
{
public:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;
    FArray() : Data(0), ArrayNum(0), ArrayMax(0) {}
    ~FArray()
    {
        if (Data)
        {
            GMalloc->Free(Data);
            Data = 0;
        }
        ArrayNum = ArrayMax = 0;
    }
    void Remove(INT Index, INT Count, INT ElementSize);
};

template <class T> class TArray : public FArray
{
public:
    TArray() {}
    ~TArray() { Remove(0, ArrayNum, sizeof(T)); }
};

struct Unnamed_Elem90 { char Pad[0x90]; };
struct Unnamed_Elem3c { char Pad[0x3c]; };
struct Unnamed_Elem30 { char Pad[0x30]; };

template class TArray<Unnamed_Elem90>;
template class TArray<Unnamed_Elem3c>;
template class TArray<Unnamed_Elem30>;

// Scaffolding for the link, not part of the unit.
void Escape(void *);
void Driver_a52b0(TArray<Unnamed_Elem90> *A) { Escape(&GMalloc); A->~TArray<Unnamed_Elem90>(); }
void Driver_a5320(TArray<Unnamed_Elem3c> *A) { Escape(&GMalloc); A->~TArray<Unnamed_Elem3c>(); }
void Driver_a5390(TArray<Unnamed_Elem30> *A) { Escape(&GMalloc); A->~TArray<Unnamed_Elem30>(); }

// RVA 0xa5400: Unreal-style InternalConstructor placement thunk
// (new((EInternal*)X) TClass()). The constructed class is unidentified, so
// a neutral name is used. Its constructor at RVA 0xa5440 was link-time
// generated and takes "this" on the stack (ret 4); it is declared as a
// __stdcall function taking the object, and the inline constructor forwards
// to it.
enum EInternal { EC_Internal };
inline void *operator new(unsigned int, EInternal *Mem) { return Mem; }
inline void operator delete(void *, EInternal *) {}

class UnnamedClass_a5440;
void __stdcall UnnamedClass_a5440_Construct(UnnamedClass_a5440 *This); /* RVA 0xa5440 */

class UnnamedClass_a5440 {
public:
    UnnamedClass_a5440() { UnnamedClass_a5440_Construct(this); }
};

void InternalConstructor_a5400(void *X)
{
    new ((EInternal *)X) UnnamedClass_a5440();
}
