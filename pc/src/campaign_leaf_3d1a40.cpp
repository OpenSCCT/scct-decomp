// campaign_leaf_3d1a40.cpp -- one function at file offset 0x3d1a40, preferred VA 0x10cd1a40. It
// reads the local time with GetLocalTime and stores its eight fields, widened, through the eight
// parameters in SYSTEMTIME order. The function and parameter names are invented; the import is
// named by the retail import table, and the bytes are the binary's.

#include "campaign_import_GetLocalTime.h"

// Unk_10cd1a40
void Unk_10cd1a40(int& Year, int& Month, int& DayOfWeek, int& Day, int& Hour, int& Minute,
    int& Second, int& Millisecond)
{
    SYSTEMTIME Time;

    GetLocalTime(&Time);
    Year = Time.wYear;
    Month = Time.wMonth;
    DayOfWeek = Time.wDayOfWeek;
    Day = Time.wDay;
    Hour = Time.wHour;
    Minute = Time.wMinute;
    Second = Time.wSecond;
    Millisecond = Time.wMilliseconds;
}
