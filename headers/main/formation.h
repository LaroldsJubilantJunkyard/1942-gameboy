#ifndef FORMATION_HEADER 
#define FORMATION_HEADER set
#include <gb/gb.h>
typedef struct FormationPath{

    uint8_t path;
    uint16_t delay;
    uint8_t position;
    uint8_t offsetX;
    uint8_t offsetY;
} FormationPath;

typedef struct Formation{

    uint8_t type;
    uint8_t count;

    FormationPath paths[];
} Formation;

extern const Formation AllFormations[];


extern const Formation TenGrey_TurnTowardsPlayer_Rightwards;
extern const Formation TenGrey_TurnTowardsPlayer_Leftwards;
#endif