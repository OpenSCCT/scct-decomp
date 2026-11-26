#include "campaign_name_index.h"

struct AnimationClip { struct Name name; unsigned char reserved[0x44]; };
struct AnimationBank {
    unsigned char reserved[0x44];
    struct AnimationClip *clips;
    int count;
};
struct AnimationBankValue { struct AnimationBank *ptr; };
struct AnimationResource { unsigned char reserved[0x210]; struct AnimationBank *default_bank; };
struct AnimationMesh;
struct MeshResourceMethods {
    void *reserved[34];
    struct AnimationResource *(__fastcall *resource)(struct AnimationMesh *);
};
struct AnimationMesh {
    const struct MeshResourceMethods *methods;
    unsigned char reserved[0x74];
    struct AnimationBank **banks;
    int count;
};
extern int __fastcall register_bank(struct AnimationMesh *, struct AnimationBankValue);

struct AnimationClip *__fastcall find_clip(struct AnimationMesh *mesh, struct Name name)
{
    int i, j;
    if (!mesh->count && mesh->methods->resource(mesh)->default_bank) {
        struct AnimationBankValue bank;
        bank.ptr = mesh->methods->resource(mesh)->default_bank;
        register_bank(mesh, bank);
    }
    for (i = 0; i < mesh->count; ++i) {
        struct AnimationBank *bank = mesh->banks[i];
        if (bank) {
            for (j = 0; j < bank->count; ++j) {
                if (name.value == bank->clips[j].name.value)
                    return &mesh->banks[i]->clips[j];
            }
        }
    }
    return 0;
}
