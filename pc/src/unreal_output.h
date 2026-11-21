// unreal_output.h -- an output device that collects text in a string
#ifndef UNREAL_OUTPUT_H
#define UNREAL_OUTPUT_H

#include "unreal_containers.h"
#include "unreal_script.h"

class FStringOutputDevice : public FOutputDevice, public FString {
public:
    FStringOutputDevice(const TCHAR *InStr = (const TCHAR *)L"") : FString(InStr) {}
    void Serialize(const TCHAR *Data, EName Event);
};

#endif // UNREAL_OUTPUT_H
