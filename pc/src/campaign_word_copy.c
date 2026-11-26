#include "campaign_word.h"
struct Source { const struct CampaignWord *word; };

struct CampaignWord *__fastcall copy_76f7c0(struct CampaignWord *out, struct Source from)
{
    *out = *from.word;
    return out;
}
