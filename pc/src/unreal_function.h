// unreal_function.h -- UFunction
#ifndef UNREAL_FUNCTION_H
#define UNREAL_FUNCTION_H

#include "unreal_field.h"

#ifdef SCCT_VERSUS

// Core.Function: 0x7c bytes, 34 virtual functions
class UFunction : public UStruct {
public:
    virtual ~UFunction();

    BYTE unk_68[0x14];
};

#endif // SCCT_VERSUS

#endif // UNREAL_FUNCTION_H
