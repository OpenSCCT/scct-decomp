// versus_unicows_resolve.cpp -- Microsoft Layer for Unicode resolver

#include "versus_unicows_resolve_private.h"

/*
================
GetOrdinal
================
*/
unsigned short __stdcall GetOrdinal(const char *name, int nameCount,
                                    const unsigned char *imageBase,
                                    const unsigned long *nameRvas,
                                    const unsigned short *ordinals)
{
    int low = 0;
    int high = nameCount - 1;
    int middle;

    while (high >= low) {
        int comparison;

        middle = (low + high) >> 1;
        comparison = strcmp(name, (const char *)imageBase + nameRvas[middle]);
        if (comparison < 0) {
            high = middle - 1;
        } else if (comparison > 0) {
            low = middle + 1;
        } else {
            break;
        }
    }

    if (high < low) {
        return -1;
    }
    return ordinals[middle];
}

/*
================
ImageEntryToDataC
================
*/
unsigned char *__stdcall ImageEntryToDataC(const unsigned char *imageBase,
                                           unsigned short directoryIndex,
                                           unsigned long *directorySize)
{
    const unsigned char *ntHeaders;
    unsigned long directoryRva;

    ntHeaders = imageBase + *(const long *)(imageBase + 0x3c);
    if (ntHeaders == 0
        || directoryIndex >= *(const unsigned long *)(ntHeaders + 0x74)) {
        goto failure;
    }

    directoryRva = *(const unsigned long *)(ntHeaders + 0x78 + directoryIndex * 8);
    if (directoryRva == 0) {
        goto failure;
    }

    *directorySize = *(const unsigned long *)(ntHeaders + 0x7c + directoryIndex * 8);
    return (unsigned char *)imageBase + directoryRva;

failure:
    *directorySize = 0;
    return 0;
}

/*
================
strcmpiC
================
*/
int __stdcall strcmpiC(const char *first, const char *second)
{
    enum {
        UNICOWS_ENGLISH_US = 0x409,
        UNICOWS_IGNORE_CASE = 1,
        UNICOWS_COMPARE_EQUAL = 2
    };

    return g_unicowsCompareStringA(UNICOWS_ENGLISH_US, UNICOWS_IGNORE_CASE,
                                   first, -1, second, -1) == UNICOWS_COMPARE_EQUAL;
}

/*
================
strncpyC
================
*/
char *__stdcall strncpyC(char *destination, const char *source, unsigned int count)
{
    char *result = destination;

    while (count != 0) {
        if ((*destination++ = *source++) == '\0') {
            break;
        }
        --count;
    }

    if (count != 0) {
        --count;
        if (count != 0) {
            memset(destination, 0, count);
        }
    }

    return result;
}

/*
================
GetProcAddressInternal
================
*/
void *__stdcall GetProcAddressInternal(void *module, const char *name)
{
    UnicowsImageExportDirectory *exports;
    unsigned short ordinal;
    unsigned long functionAddress;
    unsigned long exportEnd;
    unsigned long exportSize;
    void *moduleBase;

    if (module == 0 || name == 0) {
        return 0;
    }

    moduleBase = module;
    exports = (UnicowsImageExportDirectory *)ImageEntryToDataC(
        (const unsigned char *)moduleBase, 0, &exportSize);
    if (exports == 0) {
        return 0;
    }

    ordinal = GetOrdinal(name, (int)exports->NumberOfNames,
                         (const unsigned char *)moduleBase,
                         (const unsigned long *)((const unsigned char *)moduleBase
                             + exports->AddressOfNames),
                         (const unsigned short *)((const unsigned char *)moduleBase
                             + exports->AddressOfNameOrdinals));
    if ((unsigned long)ordinal >= exports->NumberOfFunctions) {
        return 0;
    }

    functionAddress = (unsigned long)moduleBase + *(const unsigned long *)((const unsigned char *)moduleBase
        + exports->AddressOfFunctions + ordinal * sizeof(unsigned long));
    if (functionAddress > (unsigned long)exports) {
        exportEnd = exportSize + (unsigned long)exports;
        if (functionAddress < exportEnd) {
            return 0;
        }
    }
    return (void *)functionAddress;
}

/*
================
driveandpathC
================
*/
void __stdcall driveandpathC(const char *path, char *drive, char *directory)
{
    unsigned int pathLength;
    const char *cursor;
    const char *lastSeparator;
    unsigned int directoryLength;

    pathLength = (unsigned int)strlen(path);
    if (pathLength >= 1 && path[1] == ':') {
        if (drive != 0) {
            strncpyC(drive, path, 2);
            drive[2] = 0;
        }
        path += 2;
    } else if (drive != 0) {
        drive[0] = 0;
    }

    lastSeparator = 0;
    cursor = path;
    while (*cursor != 0) {
        if (*cursor == '/' || *cursor == '\\') {
            lastSeparator = cursor + 1;
        }
        ++cursor;
    }

    if (lastSeparator != 0 && directory != 0) {
        directoryLength = (unsigned int)(lastSeparator - path);
        if (directoryLength > 0xff) {
            directoryLength = 0xff;
        }
        strncpyC(directory, path, directoryLength);
        directory[directoryLength] = 0;
    } else if (directory != 0) {
        directory[0] = 0;
    }

}

/*
================
LoadGodot
================
*/
void *LoadGodot(void)
{
    void *module;

    if (unk_2d1b20 != 0) {
        module = unk_2d1b20();
        if (module != 0) {
            goto done;
        }
    }

    {
        char systemDirectory[264];
        char windowsDirectory[264];
        char modulePath[264];
        char executablePath[264];
        unsigned long bufferSize;

        module = g_unicowsLoadLibraryA(g_unicowsModuleCache[0].Name);
        if (module != 0) {
            char directory[256];
            char drive[3];
            UnicowsGetModuleFileNameA getModuleFileName;

            bufferSize = 0x104;
            if (g_unicowsGetSystemDirectoryA(systemDirectory, bufferSize) == 0) {
                systemDirectory[0] = 0;
            }
            if (g_unicowsGetWindowsDirectoryA(windowsDirectory, bufferSize) == 0) {
                windowsDirectory[0] = 0;
            }
            getModuleFileName = g_unicowsGetModuleFileNameA;
            if (getModuleFileName(module, modulePath, bufferSize) == 0) {
                modulePath[0] = 0;
            }
            if (getModuleFileName(g_unicowsGetModuleHandleA(0), executablePath,
                                  bufferSize) == 0) {
                executablePath[0] = 0;
            }

            driveandpathC(executablePath, drive, directory);
            executablePath[(unsigned int)strlen(drive)
                           + (unsigned int)strlen(directory) + 1] = 0;
            driveandpathC(modulePath, drive, directory);
            modulePath[(unsigned int)strlen(drive)
                       + (unsigned int)strlen(directory) + 1] = 0;

            if ((!strcmpiC(windowsDirectory, modulePath)
                 && strcmpiC(windowsDirectory, executablePath))
                || (!strcmpiC(systemDirectory, modulePath)
                    && strcmpiC(systemDirectory, executablePath))) {
                g_unicowsFreeLibrary(module);
                module = 0;
            }
        }

        if (module != 0) {
            goto done;
        }

        {
            void *key;
            void *loadedRegistry;
            UnicowsRegOpenKeyExA regOpenKeyExA;
            UnicowsRegQueryValueExA regQueryValueExA;
            unsigned long commonFilesLength;

            key = 0;
            loadedRegistry = g_unicowsLoadLibraryA(advapi32_dll);
            if (g_unicowsInterlockedExchange((long *)&g_unicowsModuleCache[4].Handle,
                                             (long)loadedRegistry) != 0) {
                g_unicowsFreeLibrary(loadedRegistry);
            }
            if (g_unicowsModuleCache[4].Handle == 0) {
                goto done;
            }

            regOpenKeyExA = (UnicowsRegOpenKeyExA)GetProcAddressInternal(
                g_unicowsModuleCache[4].Handle,
                                                                         s_reg_open_key_ex_a);
            regQueryValueExA = (UnicowsRegQueryValueExA)GetProcAddressInternal(
                g_unicowsModuleCache[4].Handle,
                                                                               s_reg_query_value_ex_a);
            if (regOpenKeyExA == 0 || regQueryValueExA == 0) {
                goto done;
            }

            if (regOpenKeyExA((void *)0x80000002, s_windows_current_version, 0, 1, &key) != 0) {
                goto done;
            }

            commonFilesLength = 0x104;
            executablePath[0] = 0;
            if (regQueryValueExA(key, s_common_files_dir, 0, 0,
                                 (unsigned char *)executablePath, &commonFilesLength) == 0) {
                strcat(executablePath, s_mslu_directory_suffix);
                strcat(executablePath, g_unicowsModuleCache[0].Name);
                module = g_unicowsLoadLibraryA(executablePath);
            }

            g_unicowsRegCloseKey(key);
        }
    }

done:
    return module;
}
