#include "ABomb.hpp"
#include "Exception.hpp"
#include "GameEngine.hpp"
#include "Flame.hpp"

ABomb::ABomb(int x, int y, t_gameinfo &gameInfo)
  : ALivingEntity(x, y, BOMB, gameInfo)
{
  _timeout = 3 * gameInfo.set.getVar(FPS);
}

ABomb::~ABomb()
{
}

void	ABomb::explode()
{
  _gameInfo.map.addEntity(new Flame(_x, _y, _power, _range, ALLDIR, _gameInfo));
  _toDestroy = true;
}

void	ABomb::update()
{
  if ((--_timeout) == 0)
    this->explode();
}

void	ABomb::takeDamages(int /*amount*/)
{
  explode();
}
