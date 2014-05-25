#include "GameEngine.hpp"
#include "Box.hpp"

Box::Box(int x, int y, eType type, t_gameinfo &gameInfo)
  : AEntity(x, y, type, gameInfo)
{
}

Box::~Box()
{
}

void	Box::takeDamages(int)
{
  spawnItem(_gameInfo);
  destroy();
}

void	Box::spawnItem(t_gameinfo &gameInfo)
{
  gameInfo.map.addEntity(new SpeedItem(_x, _y, SPEEDITEM, gameInfo));
}

void	Box::destroy()
{
  _gameInfo.map.removeEntityByPtr(this);
  delete (this);
}
