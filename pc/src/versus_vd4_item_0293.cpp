// Item 0293: RVA 0x77ec0. LTCG unit (this in EAX, first byte argument in CL).
// Class and member names are neutral: no symbol evidence ties this to a
// known Unreal class. It stores two flags and writes a grey brightness colour
// (byte replicated into all four channels) into a render target object.
typedef unsigned char BYTE;
typedef unsigned long DWORD;
typedef int INT;
typedef float FLOAT;


struct UnnamedTarget_77ec0 { BYTE Pad[0x1c]; DWORD Color; };
struct UnnamedHolder_77ec0 { BYTE Pad[0x534]; UnnamedTarget_77ec0 *Target; };
struct UnnamedOwner_77ec0 { BYTE Pad[0x2af10]; UnnamedHolder_77ec0 *Holder; };

struct UnnamedClass_77ec0
{
    BYTE Pad[4];
    BYTE bDisabled;
    BYTE Mode;
    void Set(BYTE InMode, UnnamedOwner_77ec0 *Owner, BYTE bEnabled, FLOAT Brightness);
};

void UnnamedClass_77ec0::Set(BYTE InMode, UnnamedOwner_77ec0 *Owner, BYTE bEnabled, FLOAT Brightness)
{
    Mode = InMode;
    bDisabled = (bEnabled == 0);
    if (Brightness < 0.f)
        Brightness = 0.f;
    else if (Brightness > 1.f)
        Brightness = 1.f;
    DWORD V = (DWORD)(INT)(Brightness * 255.f);
    DWORD B = V & 0xff;
    Owner->Holder->Target->Color = (((V << 8 | B) << 8 | B) << 8) | B;
}

// Scaffolding for the link, not part of the unit.
void Driver_77ec0(UnnamedClass_77ec0 *C, BYTE M, UnnamedOwner_77ec0 *O, BYTE E, FLOAT F)
{
    C->Set(M, O, E, F);
}
