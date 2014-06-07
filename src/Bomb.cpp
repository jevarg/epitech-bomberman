#include "Bomb.hpp"
#include "ABomb.hpp"
#include "GameEngine.hpp"

Bomb::Bomb(int x, int y, ACharacter *character,  t_gameinfo *gameInfo, bool thread)
  : ABomb(x, y, character, gameInfo, thread)
{
  _range = MIN_RANGE;
  _power = 1;
}

Bomb::~Bomb()
{
}

AEntity *Bomb::clone(int x, int y)
{
  return (new Bomb(x, y, _character, _gameInfo));
}
