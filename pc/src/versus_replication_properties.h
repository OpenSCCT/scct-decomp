#ifndef VERSUS_REPLICATION_PROPERTIES_H
#define VERSUS_REPLICATION_PROPERTIES_H

#include "versus_pawn_action_events.h"
#include "versus_game_replication_info.h"
#include "versus_property.h"
#include "versus_net_channel.h"

enum ENetRole { ROLE_None, ROLE_DumbProxy, ROLE_SimulatedProxy, ROLE_AutonomousProxy, ROLE_Authority };

template<class T> inline T *FindObjectFast(UObject *Outer, FName Package, FName Group, FName Name, UBOOL ExactClass)
{
    return (T *)UObject::StaticFindObject(T::StaticClass(), Outer, Package, Group, Name, ExactClass);
}

template<class T> inline UBOOL NEQ(T A, T B, UPackageMap *, UActorChannel *)
{
    return A != B;
}

inline UBOOL NEQ(UObject *A, UObject *B, UPackageMap *Map, UActorChannel *Channel)
{
    if (Map->CanSerializeObject(A))
        return A != B;
    Channel->bActorMustStayDirty = 1;
    return B != 0;
}
inline UBOOL NEQ(ATeamInfo *A, ATeamInfo *B, UPackageMap *Map, UActorChannel *Channel)
{
    return NEQ((UObject *)A, (UObject *)B, Map, Channel);
}
UBOOL NEQ(FString A, FString B, UPackageMap *Map, UActorChannel *Channel);

#define DOREP(Class, Field) \
    if (NEQ(Field, ((Class *)Recent)->Field, Map, Channel)) { \
        static UProperty *Property_##Field = FindObjectFast<UProperty>(Class::StaticClass(), NAME_None, NAME_None, NAME_##Field, 0); \
        *Ptr++ = Property_##Field->RepIndex; \
    }

#define DOREPARRAY(Class, Field) \
    { \
        static UProperty *Property_##Field = FindObjectFast<UProperty>(Class::StaticClass(), NAME_None, NAME_None, NAME_##Field, 0); \
        for (INT i = 0; i < sizeof(Field) / sizeof(Field[0]); ++i) \
            if (NEQ(Field[i], ((Class *)Recent)->Field[i], Map, Channel)) \
                *Ptr++ = Property_##Field->RepIndex + i; \
    }

#endif
