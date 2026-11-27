#include "versus_interaction_array.h"
#include "unreal_script.h"
#include "versus_interaction_types.h"
#include "versus_viewport_types.h"

class UClient : public UObject {
public:
    class UEngine *Engine;
    TArray<UViewport *> Viewports;
};

class UInteractionMaster : public UInteractions {
public:
    UClient *Client;
    UInteraction *BaseMenu;
    UInteraction *Console;
    TArray<UInteraction *> GlobalInteractions;

    void MasterProcessPreRender(UCanvas *Canvas);
    void MasterProcessPostRender(UCanvas *Canvas);
    void eventProcess_PreRender(TArray<UInteraction *> Interactions, UCanvas *Canvas);
    void eventProcess_PostRender(TArray<UInteraction *> Interactions, UCanvas *Canvas);
};

namespace InteractionEventNames {
#define REGISTER_NAME(symbol, index, flags, text) const EName NAME_##symbol = static_cast<EName>(index);
#include "versus_hardcoded_names.inl"
#undef REGISTER_NAME
}

struct FInteractionRenderParams {
    TArray<UInteraction *> Interactions;
    UCanvas *Canvas;
};

void UInteractionMaster::eventProcess_PreRender(TArray<UInteraction *> Interactions, UCanvas *Canvas)
{
    FInteractionRenderParams Parms;
    Parms.Interactions = Interactions;
    Parms.Canvas = Canvas;
    ProcessEvent(FindFunctionChecked(InteractionEventNames::NAME_Process_PreRender, 0), &Parms, 0);
}

void UInteractionMaster::eventProcess_PostRender(TArray<UInteraction *> Interactions, UCanvas *Canvas)
{
    FInteractionRenderParams Parms;
    Parms.Interactions = Interactions;
    Parms.Canvas = Canvas;
    ProcessEvent(FindFunctionChecked(InteractionEventNames::NAME_Process_PostRender, 0), &Parms, 0);
}

void UInteractionMaster::MasterProcessPreRender(UCanvas *Canvas)
{
    for (INT i = 0; i < Client->Viewports.Num(); i++)
        eventProcess_PreRender(Client->Viewports(i)->LocalInteractions, Canvas);
    for (INT i = 0; i < GlobalInteractions.Num(); i++) {
        UInteraction *Interaction = GlobalInteractions(i);
        if (Interaction->bNativeEvents && Interaction->bVisible)
            Interaction->NativePreRender(Canvas);
    }
    eventProcess_PreRender(GlobalInteractions, Canvas);
}

void UInteractionMaster::MasterProcessPostRender(UCanvas *Canvas)
{
    for (INT i = 0; i < Client->Viewports.Num(); i++)
        eventProcess_PostRender(Client->Viewports(i)->LocalInteractions, Canvas);
    for (INT i = 0; i < GlobalInteractions.Num(); i++) {
        UInteraction *Interaction = GlobalInteractions(i);
        if (Interaction->bNativeEvents && Interaction->bVisible)
            Interaction->NativePostRender(Canvas);
    }
    eventProcess_PostRender(GlobalInteractions, Canvas);
}
