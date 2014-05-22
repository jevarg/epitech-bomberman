#include "ABomb.hpp"
#include "Exception.hpp"
#include "GameEngine.hpp"
#include "Flame.hpp"

ABomb::ABomb(int x, int y, t_gameinfo &gameInfo)
  : ALivingEntity(x, y, BOMB, gameInfo)
{
  _timeout = 2 * gameInfo.set.getVar(FPS);
}

ABomb::~ABomb()
{
}

void	ABomb::explode(Map &map)
{
  Flame	*newFlame = new Flame(_x, _y, _power, ALLDIR, _gameInfo);
  newFlame->setFire(_x, _y, ALLDIR, _range);
  delete(this);
}

void	ABomb::update()
{
}
  
void	ABomb::takeDamages(int /*amount*/)
{

}
