#include "Bomb.hpp"
#include "ABomb.hpp"
#include "GameEngine.hpp"

/* get the fuck out those "model" parameters from constructors */
Bomb::Bomb(int x, int y, IObject *bombModel, t_gameinfo &gameInfo)
  : ABomb(x, y, bombModel, gameInfo)
{
  _range = 5;
  _power = 1;
}

Bomb::~Bomb()
{
}

void	Bomb::update(t_gameinfo &gameInfo)
{
  (void)gameInfo;
}
