/* RVA 0xadc20: placement construction of an AController subclass (vtable at
   0x10c052a8, class not yet identified, so UnnamedController_adc20). The
   object was compiled with /GL: AController's constructor (0xacab0) takes
   the object on the stack under LTCG and can throw, so the placement new
   keeps its exception frame for the matching placement delete. */
typedef unsigned int size_t;

inline void *operator new(size_t, void *Mem) { return Mem; }
inline void operator delete(void *, void *) {}

class AActor {
public:
    AActor();
    virtual ~AActor();
    unsigned char ActorFields[0x54c - 4];
};

// Twelve-byte element of the array AController builds at +0x54c.
struct FControllerSlot_54c {
    FControllerSlot_54c();
    ~FControllerSlot_54c();
    unsigned int Words[3];
};

class AController : public AActor {
public:
    AController();
    virtual ~AController();
    FControllerSlot_54c Slots[4];
};

class UnnamedController_adc20 : public AController {
public:
    UnnamedController_adc20() {}
    virtual ~UnnamedController_adc20();
};

void place_UnnamedController_adc20(void *Mem)
{
    new (Mem) UnnamedController_adc20;
}

// Scaffolding for the link, not part of the unit: stand-ins for retail
// AActor::AActor (0x92100) and AController::AController (0xacab0), so the
// linker sees their callers and gives them the retail conventions.
__declspec(noinline) AActor::AActor() { ActorFields[0] = 0; }
__declspec(noinline) AController::AController() {}
void Driver_adc20(void *Mem) { place_UnnamedController_adc20(Mem); }
