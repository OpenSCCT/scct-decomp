struct Component;
struct Handler;
struct Child { unsigned reserved; unsigned char enabled, padding[39]; struct Handler *handler; };
struct Component {
    unsigned prefix[10];
    struct Child **first, **last;
    unsigned reserved;
    float time;
    int interval;
    unsigned char flag, enabled, padding[6];
    int *steps;
};
extern void __fastcall run_child(struct Child *);

void __fastcall run_children(struct Component *component)
{
    struct Child **it;
    if (component->enabled) {
        for (it = component->first; it != component->last; ++it)
            run_child(*it);
    }
}
