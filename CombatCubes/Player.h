#pragma once
#include <vector>
#include "Unit.h"

using namespace std;
class Player
{
public:
  Player();
  ~Player();

  void addUnit(Unit *newUnit);

  void drawPlayer();

private:
  vector<Unit *> m_units;
};

