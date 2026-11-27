#include "versus_mgm_localize.h"
#include "versus_name_registry.h"

const TCHAR *Localize(const TCHAR *Section, const TCHAR *Key, const TCHAR *Package);

extern const TCHAR *GMgmLocalizationPackage;
extern const TCHAR *GMgmLocalizationSection;

const TCHAR *LocalizeMgm(FName Name)
{
    return Localize(GMgmLocalizationSection, FName_Names(Name.Index)->Name, GMgmLocalizationPackage);
}
