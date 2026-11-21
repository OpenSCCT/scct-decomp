// AActor key/value pair slots at 0x10c (four {key, value} pairs), cleared by
// the AActor initializer (see versus_actor_placement.c). Bit 0 of the flags
// word at 0x2e8 disables the table. Names are neutral; the field meaning is
// not recovered.
struct actor_pair {
    unsigned int key;
    unsigned int value;
};

struct actor_base {
    const void *methods;
    unsigned char fields_before_pairs[0x10c - 4];
    actor_pair pairs[4];
    unsigned char fields_before_flags[0x2e8 - 0x12c];
    unsigned int flags;

    __declspec(noinline) unsigned int FindPairValue(unsigned int key);
    __declspec(noinline) void ClearPair(unsigned int key);
};

unsigned int actor_base::FindPairValue(unsigned int key)
{
    if (flags & 1)
        return 0;
    for (int i = 0; i < 4; i++) {
        if (pairs[i].key == key)
            return pairs[i].value;
    }
    return 0;
}

void actor_base::ClearPair(unsigned int key)
{
    if (flags & 1)
        return;
    for (int i = 0; i < 4; i++) {
        if (pairs[i].key == key) {
            pairs[i].key = 0;
            pairs[i].value = 0;
            return;
        }
    }
}

// Scaffolding for the link, not part of the unit.
void Escape(void *);
unsigned int Driver_92150(actor_base *a, unsigned int k) { return a->FindPairValue(k); }
void Driver_92180(actor_base *a, unsigned int k) { a->ClearPair(k); }
