// campaign_import_PostThreadMessageW.h -- a function imported from USER32.dll.
// The retail import table names it PostThreadMessageW.

#ifndef CAMPAIGN_IMPORT_POSTTHREADMESSAGEW_H
#define CAMPAIGN_IMPORT_POSTTHREADMESSAGEW_H

extern "C" __declspec(dllimport) int __stdcall PostThreadMessageW(unsigned long Thread,
                                                                  unsigned int Message,
                                                                  unsigned int WParam, long LParam);

#endif
