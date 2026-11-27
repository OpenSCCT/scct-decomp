#ifndef VERSUS_GUI_CONTROLLER_TYPES_H
#define VERSUS_GUI_CONTROLLER_TYPES_H

#include "versus_interaction_types.h"

class UGUIPage;

// Engine and GUI register these classes with sizes 0xc50 and 0xe9c.
class UBaseGUIController : public UInteraction {
public:
    BYTE unk_34[0xc50 - 0x34];
};

class UGUIController : public UBaseGUIController {
public:
    virtual ~UGUIController();
    virtual UBOOL NativeKeyEvent(BYTE &iKey, BYTE &State, FLOAT Delta);
    virtual void NativeTick(FLOAT DeltaTime);
    virtual void NativePreRender(UCanvas *Canvas);
    virtual void NativePostRender(UCanvas *Canvas);

    BYTE unk_c50[0xc80 - 0xc50];
    UGUIPage *ActivePage;
    BYTE unk_c84[0x48];
    INT MouseX;
    INT MouseY;
    INT LastMouseX;
    INT LastMouseY;
    BYTE unk_cdc[0x14];
    FLOAT ButtonRepeatDelay;
    BYTE RepeatKey;
    FLOAT RepeatDelta;
    FLOAT RepeatTime;
    FLOAT CursorFade;
    INT CursorStep;
    FLOAT FastCursorFade;
    INT FastCursorStep;
    BYTE unk_d10[0xe9c - 0xd10];

    UBOOL HasMouseMoved() const
    {
        return MouseX != LastMouseX || MouseY != LastMouseY;
    }
};

#endif
