static const struct InGameTrade sInGameTrades[] = {
    [INGAME_TRADE_MR_MIME] = // 0
    {
        .nickname = _("Hugs"),
        .species = SPECIES_GASTLY,
        .ivs = {31, 0, 31, 31, 31, 31},
        .otId = 1985,
        .conditions = {0, 0, 0, 255, 0}, // cool, beauty, cute, smart, tough
        .personality = NATURE_TIMID,
        .heldItem = ITEM_BLACK_SLUDGE,
        .mailNum = 255,
        .otName = _("REYLEY"),
        .otGender = MALE,
        .sheen = 10,
        .customAbility = ABILITY_NORMALIZE
    },
    [INGAME_TRADE_JYNX] = // 1
    {
        .nickname = _("Wingnut"),
        .species = SPECIES_FLETCHLING,
        .ivs = {31, 31, 31, 31, 31, 31},
        .otId = 36728,
        .conditions = {0, 0, 0, 255, 0}, // cool, beauty, cute, smart, tough
        .personality = NATURE_HASTY,
        .heldItem = ITEM_CHOICE_SCARF,
        .mailNum = 0,
        .otName = _("DONTAE"),
        .otGender = MALE,
        .sheen = 10,
        .customAbility = ABILITY_DOWNLOAD
    },
    [INGAME_TRADE_NIDORAN] = // 2 (Cerulean City - Vermilion City)
    {
        .nickname = _("Ms. Happy"),
        .species = SPECIES_HAPPINY,
        .ivs = {31, 0, 31, 31, 31, 31},
        .otId = 63184,
        .conditions = {0, 0, 255, 0, 0}, // cool, beauty, cute, smart, tough
        .personality = NATURE_BOLD, // We want BOLD nature (5), so personality % 25 must be 5.
        .heldItem = ITEM_ASSAULT_VEST,
        .mailNum = 255,
        .otName = _("SAIGE"),
        .otGender = FEMALE,
        .sheen = 10,
        .customAbility = ABILITY_REGENERATOR
    },
    [INGAME_TRADE_FARFETCHD] = // 3
    {
        .nickname = _("Fishy"),
        .species = SPECIES_MAGIKARP,
        .ivs = {31, 31, 31, 31, 31, 31},
        .otId = 8810,
        .conditions = {0, 0, 0, 0, 255}, // cool, beauty, cute, smart, tough
        .personality = NATURE_JOLLY,
        .heldItem = ITEM_LIFE_ORB,
        .mailNum = 255,
        .otName = _("DANIELLE"),
        .otGender = FEMALE,
        .sheen = 10,
        .customAbility = ABILITY_VOLT_ABSORB
    },
    [INGAME_TRADE_NIDORINOA] = // 4 (Gate House)
    {
        .nickname = _("Sugma"),
        .species = SPECIES_SLUGMA,
        .ivs = {31, 0, 31, 31, 31, 31},
        .otId = 13637,
        .conditions = {255, 0, 0, 0, 0}, // cool, beauty, cute, smart, tough
        .personality = NATURE_CALM,
        .heldItem = ITEM_HEAT_ROCK,
        .mailNum = 255,
        .otName = _("TURNER"),
        .otGender = MALE,
        .sheen = 10,
        .customAbility = ABILITY_DROUGHT
    },
    [INGAME_TRADE_LICKITUNG] = // 5 (Gate House)
    {
        .nickname = _("Moist"),
        .species = SPECIES_FERROSEED,
        .ivs = {31, 31, 31, 31, 31, 31},
        .otId = 1239,
        .conditions = {255, 0, 0, 0, 0}, // cool, beauty, cute, smart, tough
        .personality = NATURE_SASSY,
        .heldItem = ITEM_DAMP_ROCK,
        .mailNum = 255,
        .otName = _("HADEN"),
        .otGender = MALE,
        .sheen = 10,
        .customAbility = ABILITY_DRIZZLE
    },
    // These three are extremely good, so there will be a high cost to obtaining them in addition to their late-game appearance.
    [INGAME_TRADE_ELECTRODE] = // 6 (Pokemon Lab: Lounge)
    {
        .nickname = _("Noisy"),
        .species = SPECIES_NOIBAT,
        .ivs = {31, 0, 31, 31, 31, 31},
        .otId = 50298,
        .conditions = {0, 0, 0, 0, 255}, // cool, beauty, cute, smart, tough
        .personality = NATURE_TIMID,
        .heldItem = ITEM_CHOICE_SPECS,
        .mailNum = 255,
        .otName = _("CLIFTON"),
        .otGender = MALE,
        .sheen = 10,
        .customAbility = ABILITY_AERILATE
    },
    // These three are extremely good, so there will be a high cost to obtaining them in addition to their late-game appearance.
    [INGAME_TRADE_TANGELA] = // 7 (Pokemon Lab: Lounge)
    {
        .nickname = _("Soul"),
        .species = SPECIES_MAGEARNA,
        .ivs = {31, 0, 31, 31, 31, 31},
        .otId = 60042,
        .conditions = {255, 255, 0, 0, 0}, // cool, beauty, cute, smart, tough
        .personality = NATURE_CALM,
        .heldItem = ITEM_ASSAULT_VEST,
        .mailNum = 255,
        .otName = _("NORMA"),
        .otGender = FEMALE,
        .sheen = 10,
        .customAbility = ABILITY_REGENERATOR
    },
    // These three are extremely good, so there will be a high cost to obtaining them in addition to their late-game appearance.
    [INGAME_TRADE_SEEL] = // 8 (Pokemon Lab: Experiment Room)
    {
        .nickname = _("Nyaa"),
        .species = SPECIES_MEW,
        .ivs = {31, 31, 31, 31, 31, 31},
        .otId = 9853,
        .conditions = {0, 255, 255, 0, 0}, // cool, beauty, cute, smart, tough
        .personality = NATURE_JOLLY,
        .heldItem = ITEM_LEFTOVERS,
        .mailNum = 255,
        .otName = _("GARETT"),
        .otGender = MALE,
        .sheen = 10,
        .customAbility = ABILITY_UNAWARE
    },
};

static const u16 sInGameTradeMailMessages[][10] = {
    {
        EC_WORD_THAT_S,
        EC_WORD_A,
        EC_WORD_HEALTHY,
        EC_POKEMON(JYNX),
        EC_WORD_EXCL,
        EC_WORD_BE,
        EC_WORD_KIND,
        EC_WORD_TO,
        EC_WORD_IT
    }
};
