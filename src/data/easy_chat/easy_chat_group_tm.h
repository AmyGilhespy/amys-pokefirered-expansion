// src/data/easy_chat/easy_chat_group_tms.h

#ifndef GUARD_EASYCHAT_GROUP_TM_H
#define GUARD_EASYCHAT_GROUP_TM_H

#include "constants/tms_hms.h"
#include "item.h"

static const u8 sEasyChatWord_Fuck[] = _("FUCK");
static const u16 sEasyChatGroup_Tm[] = {
0,
#define EACH_TM(id) ITEM_TM_ ## id - ITEM_TM01 + 1,
#define EACH_HM(id) ITEM_HM_ ## id - ITEM_TM01 + 1,
FOREACH_TM(EACH_TM)
FOREACH_HM(EACH_HM)
#undef EACH_TM
#undef EACH_HM
};

#endif // GUARD_EASYCHAT_GROUP_TM_H

