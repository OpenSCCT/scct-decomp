/* campaign_cleanup_aliases.c -- forwarding cleanup thunks at known Campaign entries. */
struct Record;

extern void __fastcall destroy_4989e0(struct Record *object);
extern void __fastcall destroy_4df400(struct Record *object);
extern void __fastcall cleanup_5fcf90(struct Record *object);
extern void __fastcall cleanup_601820(struct Record *object);
extern void __fastcall cleanup_60bb40(struct Record *object);
extern void __fastcall cleanup_604690(struct Record *object);
extern void __fastcall cleanup_729200(struct Record *object);
extern void __fastcall cleanup_730db0(struct Record *object);

/* destroy_4c7610 */
void __fastcall destroy_4c7610(struct Record *object)
{
    destroy_4989e0(object);
}

/* destroy_4df680 */
void __fastcall destroy_4df680(struct Record *object)
{
    destroy_4df400(object);
}

/* cleanup_5fd730 */
void __fastcall cleanup_5fd730(struct Record *object)
{
    cleanup_5fcf90(object);
}

/* cleanup_601930 */
void __fastcall cleanup_601930(struct Record *object)
{
    cleanup_601820(object);
}

/* cleanup_60bf10 */
void __fastcall cleanup_60bf10(struct Record *object)
{
    cleanup_60bb40(object);
}

/* cleanup_61c8a0 */
void __fastcall cleanup_61c8a0(struct Record *object)
{
    cleanup_604690(object);
}

/* cleanup_722d70 */
void __fastcall cleanup_722d70(struct Record *object)
{
    cleanup_5fcf90(object);
}

/* cleanup_72ba10 */
void __fastcall cleanup_72ba10(struct Record *object)
{
    cleanup_729200(object);
}

/* cleanup_7294a0 */
void __fastcall cleanup_7294a0(struct Record *object)
{
    cleanup_730db0(object);
}
