#ifndef VERSUS_INTERACTION_MASTER_H
#define VERSUS_INTERACTION_MASTER_H

class UCanvas;
class UInteractionMaster : public UInteractions {
public:
    virtual ~UInteractionMaster();
    class UClient *Client;
    UInteraction *BaseMenu;
    UInteraction *Console;
    TArray<UInteraction *> GlobalInteractions;
    BYTE unk_40[4];
    void MasterProcessPreRender(UCanvas *Canvas);
    void MasterProcessPostRender(UCanvas *Canvas);
    void eventProcess_PreRender(TArray<UInteraction *> Interactions, UCanvas *Canvas);
    void eventProcess_PostRender(TArray<UInteraction *> Interactions, UCanvas *Canvas);
};

#endif
