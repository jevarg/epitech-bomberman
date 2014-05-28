#include "Bomb.hpp"
#include "ABomb.hpp"
#include "GameEngine.hpp"

Bomb::Bomb(int x, int y, ACharacter *character,  t_gameinfo &gameInfo)
  : ABomb(x, y, character, gameInfo)
{
  _range = 5;
  _power = 1;
}

Bomb::~Bomb()
{
}
