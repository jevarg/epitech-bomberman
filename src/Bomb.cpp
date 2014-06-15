#include "Bomb.hpp"
<<<<<<< HEAD
#include "ABomb.hpp"
#include "GameEngine.hpp"

Bomb::Bomb(int x, int y, ACharacter *character,  t_gameinfo *gameInfo, bool thread)
  : ABomb(x, y, character, gameInfo, thread)
{
  _range = MIN_RANGE;
  _power = 1;
=======

Bomb::Bomb()
{
>>>>>>> 35c0cf39dea90a7423e4e792261ed64446d55473
}

Bomb::~Bomb()
{
}
<<<<<<< HEAD

AEntity *Bomb::clone(int x, int y)
{
  return (new Bomb(x, y, _character, _gameInfo));
}
=======
>>>>>>> 35c0cf39dea90a7423e4e792261ed64446d55473
