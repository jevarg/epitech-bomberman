#include "ABomb.hpp"
#include "Exception.hpp"
#include "GameEngine.hpp"
#include "Flame.hpp"

ABomb::ABomb(int x, int y, IObject *bombModel, t_gameinfo &gameInfo)
  : ALivingEntity(x, y, BOMB, bombModel, gameInfo)
{
}

ABomb::~ABomb()
{
}

void	ABomb::explode(Map &map)
{
  Flame	*newFlame = new Flame(_x, _y, _power, NULL, _gameInfo);
  newFlame->setFire(_x, _y, ALLDIR, _range);
  delete(this);
}
