#include "ABomb.hpp"
#include "Exception.hpp"
#include "GameEngine.hpp"
#include "Flame.hpp"

ABomb::ABomb(int x, int y, t_gameinfo &gameInfo)
  : ALivingEntity(x, y, BOMB, gameInfo)
{
  _timeout = 1 * gameInfo.set.getVar(FPS);
}

ABomb::~ABomb()
{
}

void	ABomb::explode()
{
  die(); // importent to die first so no colision with flame
  _gameInfo.map.addEntity(new Flame(_x, _y, _power, _range, ALLDIR, _gameInfo));
}

void	ABomb::update()
{
  if ((--_timeout) == 0)
    this->explode();
}

void	ABomb::takeDamages(int /*amount*/)
{
  if (_isAlive == false)
    return ;
  explode();
}
