// Work item 0142: InternalConstructor-style placement constructors (Versus RVA 0x3e3a0, 0x3e3e0).
// Unreal's DECLARE_CLASS gives every class
//     static void InternalConstructor(void* X) { new((EInternal*)X) TClass; }
// The class names are not recovered; neutral names are used.

typedef unsigned short TCHAR;
typedef unsigned int size_t;

enum EInternal { EC_Internal };

inline void* operator new(size_t Size, EInternal* Mem) { return (void*)Mem; }
inline void operator delete(void* Object, EInternal* Mem) {}

// Constructor at RVA 0x1ebc0 (class unidentified).
class UnnamedClass_1ebc0
{
public:
    __declspec(noinline) UnnamedClass_1ebc0();
    char Pad[0x200];
};

// Constructor at RVA 0x1e930 (class unidentified); takes a string argument.
struct Base_Stand
{
    Base_Stand(const TCHAR* Name);
    ~Base_Stand();
    int Value;
};
class UnnamedClass_1e930
{
public:
    __declspec(noinline) UnnamedClass_1e930(const TCHAR* Name);
    virtual ~UnnamedClass_1e930();
    char Pad[0x30];
    Base_Stand Field;
};

// The constructors live in other LTCG units; minimal bodies stand in so the
// linker gives them retail's this-on-the-stack convention. Not part of the unit.
struct Member_Stand
{
    Member_Stand();
    ~Member_Stand();
    int Value;
};

UnnamedClass_1ebc0::UnnamedClass_1ebc0()
{
    Member_Stand A, B, C;
}
UnnamedClass_1e930::UnnamedClass_1e930(const TCHAR* Name)
    : Field(Name)
{
    Member_Stand A, B, C;
}

// L"" in retail .rdata (shared literal).
extern const TCHAR EmptyString_10928[];

void InternalConstructor_1ebc0(void* X)
{
    new((EInternal*)X) UnnamedClass_1ebc0;
}

void InternalConstructor_1e930(void* X)
{
    new((EInternal*)X) UnnamedClass_1e930(EmptyString_10928);
}

// Scaffolding for the link, not part of the unit.
void Escape(void*);
void Driver_3e3a0(void* X) { InternalConstructor_1ebc0(X); }
void Driver_3e3e0(void* X) { InternalConstructor_1e930(X); }
// Other retail callers construct this class with other names (scaffolding).
void Driver_3e3e0_Other(void* X, const TCHAR* Name) { new((EInternal*)X) UnnamedClass_1e930(Name); }
