#ifndef VERSUS_NATIVE_SUBSYSTEM_H
#define VERSUS_NATIVE_SUBSYSTEM_H

#include "versus_build.h"
#include "versus_native_class_init.h"

class USubsystem : public UObject {
public:
    virtual ~USubsystem();
    virtual void Tick(FLOAT DeltaTime);
};

#endif
