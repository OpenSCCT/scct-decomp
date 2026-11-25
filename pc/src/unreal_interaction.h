// unreal_interaction.h -- UInteractions and UInteraction
#ifndef UNREAL_INTERACTION_H
#define UNREAL_INTERACTION_H

#include "unreal_object.h"

#ifdef SCCT_VERSUS

// Engine.Interactions: 0x28 bytes, 22 virtual functions
class UInteractions : public UObject {
public:
    virtual ~UInteractions();
};

// Engine.Interaction: 0x34 bytes, 28 virtual functions
class UInteraction : public UInteractions {
public:
    virtual ~UInteraction();
    virtual void VirtualSlot22();
    virtual void VirtualSlot23();
    virtual void VirtualSlot24();
    virtual void VirtualSlot25();
    virtual void VirtualSlot26();
    virtual void VirtualSlot27();

    BYTE unk_28[0xc];
};

#else // Campaign
#include "unreal_containers.h"

extern FName name_Initialized;     // constructed from the retail name "Initialized"

// Engine.Interactions: 0x28 bytes, 24 virtual functions
class UInteractions : public UObject {
public:
    virtual ~UInteractions();
};

// Engine.Interaction: 0x34 bytes, 24 virtual functions
class UInteraction : public UInteractions {
public:
    virtual ~UInteraction();

    BYTE unk_28[0xc];

    UBOOL ConsoleCommand(FString S);
    void eventInitialized();

    DECLARE_NATIVE(execConsoleCommand)
    DECLARE_NATIVE(execInitialize)
};

#endif // SCCT_VERSUS

#endif // UNREAL_INTERACTION_H
