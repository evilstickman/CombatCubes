#include "Player.h"



Player::Player()
{
}


Player::~Player()
{
}

void Player::addUnit(Unit *newUnit)
{
  m_units.push_back(newUnit);
}

void Player::drawPlayer()
{
  for (Unit *u : m_units)
  {
    u->draw();
  }
}