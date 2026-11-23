// campaign_import_PostThreadMessageA.h -- a function imported from USER32.dll.
// The retail import table names it PostThreadMessageA.

#ifndef CAMPAIGN_IMPORT_POSTTHREADMESSAGEA_H
#define CAMPAIGN_IMPORT_POSTTHREADMESSAGEA_H

extern "C" __declspec(dllimport) int __stdcall PostThreadMessageA(unsigned long Thread,
                                                                  unsigned int Message,
                                                                  unsigned int WParam, long LParam);

#endif
