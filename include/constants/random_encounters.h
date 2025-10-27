#ifndef GUARD_CONSTANTS_RANDOM_ENCOUNTERS_H
#define GUARD_CONSTANTS_RANDOM_ENCOUNTERS_H

// How many species we store per region map section
#define RANDOM_ENCOUNTER_SLOTS_PER_REGION 3

// How many region ids we reserve space for (regionMapSectionId is a byte in many implementations)
#define RANDOM_ENCOUNTER_REGION_COUNT 256

// Sentinel for "no species"
#define RANDOM_ENCOUNTER_SPECIES_NONE 0xFFFF

#endif // GUARD_CONSTANTS_RANDOM_ENCOUNTERS_H

