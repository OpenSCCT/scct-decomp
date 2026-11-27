#include "versus_mgm_localize.h"
#include "versus_name_registry.h"

const TCHAR *Localize(const TCHAR *Section, const TCHAR *Key, const TCHAR *Package);

extern const TCHAR *GMgmLocalizationPackage;
extern const TCHAR *GMgmLocalizationSection;

const TCHAR *LocalizeMgm(FName Name)
{
    return Localize(GMgmLocalizationSection, FName_Names(Name.Index)->Name, GMgmLocalizationPackage);
}

const TCHAR *LocalizeMgm(FName Key, FName Section)
{
    return Localize(FName_Names(Section.Index)->Name, FName_Names(Key.Index)->Name, L"MagmaDynamic");
}
