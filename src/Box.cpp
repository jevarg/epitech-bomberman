#include "GameEngine.hpp"
#include "Box.hpp"

Box::Box(int x, int y, eType type, t_gameinfo &gameInfo)
  : AEntity(x, y, type, gameInfo)
{
  _facto = ItemFactory::getInstance();
}

Box::~Box()
{
}

void	Box::takeDamages(int)
{
  spawnItem(_gameInfo);
  _gameInfo.map.removeEntityByPtr(this);
  _gameInfo.map.pushToCollector(this);
}

void	Box::spawnItem(t_gameinfo &gameInfo)
{
  gameInfo.map.addEntity(_facto->getItem(SPEEDITEM, _x, _y));
}
