// campaign_import_ExitProcess.h -- the Win32 import ExitProcess (KERNEL32.dll), named by the import
// table.
#ifndef CAMPAIGN_IMPORT_EXITPROCESS_H
#define CAMPAIGN_IMPORT_EXITPROCESS_H

extern "C" __declspec(dllimport) void __stdcall ExitProcess(unsigned int ExitCode);

#endif
