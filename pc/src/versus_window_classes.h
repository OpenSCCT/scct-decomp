// versus_window_classes.h -- classes of the Window package as the Versus executable builds them
#ifndef VERSUS_WINDOW_CLASSES_H
#define VERSUS_WINDOW_CLASSES_H

#include "versus_build.h"
#include "versus_core_classes.h"

// Window.WindowManager: 0x28 bytes, 23 virtual functions
class UWindowManager : public USubsystem {
public:
    virtual ~UWindowManager();
};

#endif // VERSUS_WINDOW_CLASSES_H
