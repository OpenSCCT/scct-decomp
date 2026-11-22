// campaign_leaf_3d2390.cpp -- a free function at VA 0x10cd2390 that passes its four arguments to
// the Win32 GetPrivateProfileIntW and returns its result. The function and parameter names are
// invented; GetPrivateProfileIntW is the import's name.

extern "C" __declspec(dllimport) unsigned int __stdcall GetPrivateProfileIntW(
    const unsigned short* AppName, const unsigned short* KeyName, int Default,
    const unsigned short* FileName);

// Unk_10cd2390
unsigned int Unk_10cd2390(const unsigned short* AppName, const unsigned short* KeyName, int Default,
    const unsigned short* FileName)
{
    return GetPrivateProfileIntW(AppName, KeyName, Default, FileName);
}
