#ifndef CAMPAIGN_NATIVE_INITIALIZER_H
#define CAMPAIGN_NATIVE_INITIALIZER_H

struct ScriptObject;

typedef struct ScriptFrame {
    void *frame_prefix;
    void *node;
    struct ScriptObject *object;
    unsigned char *code;
} ScriptFrame;

/* The receiver arrives in ECX. The VM supplies the frame and result on the stack. */
typedef void (__fastcall *CampaignNative)(struct ScriptObject *, unsigned, ScriptFrame *, void *);

extern CampaignNative campaign_native_table[];
extern CampaignNative campaign_cast_table[];

unsigned char __cdecl campaign_register_native(int index, const CampaignNative *entry);

#define REGISTER_CAMPAIGN_NATIVE(name, index)                    \
    void __cdecl register_##name(void)                           \
    {                                                            \
        registration_result_##name =                             \
            campaign_register_native((index), &callback_##name); \
    }

#endif
