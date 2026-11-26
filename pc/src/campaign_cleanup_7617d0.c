/* campaign_cleanup_7617d0.c -- list cleanup thunk at VA 0x10f617d0. */
#include "sound_list.h"

extern void __fastcall list_clear_nodes_r7614a0(SndCallBackList *list);

/* cleanup_7617d0 */
void __fastcall cleanup_7617d0(SndCallBackList *list)
{
    list_clear_nodes_r7614a0(list);
}
