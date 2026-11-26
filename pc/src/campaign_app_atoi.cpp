// campaign_app_atoi.cpp -- appAtoi delegates wide-character parsing to the Toolkit CRT.

#include "unreal_containers.h"
#include <stdlib.h>

// appAtoi
INT appAtoi(const TCHAR *Str)
{
    return _wtoi(Str);
}
