#include "sound_list.h"

extern void __fastcall list_clear_nodes_r7614a0(SndCallBackList *list);

void __fastcall cleanup_7617d0(SndCallBackList *list)
{
    list_clear_nodes_r7614a0(list);
}
