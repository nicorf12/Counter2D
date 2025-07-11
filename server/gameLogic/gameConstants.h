#ifndef GAMECONSTANTS_H
#define GAMECONSTANTS_H
#include "../../common/structures.h"
enum class Role { TERRORIST, COUNTER_TERRORIST };

struct Position {
  float x;
  float y;
};
struct Spike {
  Position position;
  BombState state;
};

struct PlayerCellBounds {
  int leftCell;
  int rightCell;
  int topCell;
  int bottomCell;
};

struct DroppedWeapon {
  WeaponName name;
  float x;
  float y;
};

enum class EquippedWeapon { KNIFE, PRIMARY, SECONDARY };


#define SPEED 5.0f
#define MAX_PLAYERS_PER_TEAM 5

#define AMMO_PRICE 40
#define MAX_HEALTH 200

const float ACELERATION_RATE = 35.0f;
const float MAX_ACELERATION = 3.0f;
const float MIN_ACELERATION = -2.0f;
const float SLIDE_DURATION = 0.15f;

#endif
