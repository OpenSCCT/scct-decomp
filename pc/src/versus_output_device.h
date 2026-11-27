#ifndef VERSUS_OUTPUT_DEVICE_H
#define VERSUS_OUTPUT_DEVICE_H

#include "versus_name.h"

class FOutputDevice {
public:
    virtual void Serialize(const TCHAR *Text, EName Event) = 0;
    virtual void Flush();
    void Logf(EName Event, const TCHAR *Format, ...);
};

#endif
