#ifndef CAMPAIGN_STATIC_INSTALL_H
#define CAMPAIGN_STATIC_INSTALL_H

struct StaticMethodPrefix {
    const void *methods;
};

#define CLEANUP(Entry, Object, Methods) \
void Entry(void) \
{ \
    ((struct StaticMethodPrefix *)(void *)&Object)->methods = Methods; \
}

#endif
