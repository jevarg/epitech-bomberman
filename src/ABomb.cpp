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
  Flame	*newFlame = new Flame(_x, _y, _power, _range, ALLDIR, _gameInfo);
}

void	ABomb::update()
{
  if (--_timeout == 0)
    {
      this->explode();
      this->destroy(_gameInfo.map);
    }
}
  
void	ABomb::takeDamages(int /*amount*/)
{
}
