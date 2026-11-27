#include "versus_build.h"
#include "versus_native_class_init.h"

extern "C" void *__cdecl memcpy(void *Dest, const void *Source, unsigned int Count);
extern INT GRegistrationDepth;

inline UObject *NextRegistrant(UObject *Object)
{
    UObject *Next;
    memcpy(&Next, &Object->indexInExportMap, sizeof(Next));
    return Next;
}

inline void UObject::ConditionalRegister()
{
    if (Index == -1) {
        INT i;
        for (i = 0; i < GObjRegistrants.Num(); ++i)
            if (GObjRegistrants(i) == this)
                break;
        // The shipped editor asserts i != GObjRegistrants.Num() here. Retail omits the assertion.
        Register();
    }
}

void UObject::ProcessRegistrants()
{
    if (++GRegistrationDepth == 1) {
        INT Count = 0;
        for (UObject *Object = GAutoRegister; Object; Object = NextRegistrant(Object))
            ++Count;

        GObjRegistrants.Empty(Count);
        while (GAutoRegister) {
            GObjRegistrants.AddItem(GAutoRegister);
            GAutoRegister = NextRegistrant(GAutoRegister);
        }

        for (INT i = 0; i < GObjRegistrants.Num(); ++i)
            GObjRegistrants(i)->ConditionalRegister();
        GObjRegistrants.Empty();
    }
    --GRegistrationDepth;
}
