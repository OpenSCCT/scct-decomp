struct Normal { float x, y, z, w; };
struct Contact {
    float position[4];
    struct Normal normal;
    unsigned extra[4];
};
struct ContactArray { struct Contact *data; int count; };
struct ContactOutput { struct ContactArray *contacts; };
/* FAKEMATCH: the C fastcall declaration uses this wrapper to keep the pair
   and input addresses in the collision method's stack argument slots. */
struct PairArgument { const void *value; };
/* FAKEMATCH: this wrapper passes the collision output address on the stack. */
struct OutputArgument { struct ContactOutput *value; };

extern void __fastcall collide(void *agent, struct PairArgument first, struct PairArgument second,
                               struct PairArgument input, struct OutputArgument output);

void __fastcall collide_reversed(void *agent, struct PairArgument first, struct PairArgument second,
                                 struct PairArgument input, struct OutputArgument output)
{
    int i = output.value->contacts->count;
    collide(agent, second, first, input, output);
    for (; i < output.value->contacts->count; ++i) {
        struct Normal *normal = &output.value->contacts->data[i].normal;
        normal->x = -normal->x;
        normal->y = -normal->y;
        normal->z = -normal->z;
        normal->w = -normal->w;
    }
}
