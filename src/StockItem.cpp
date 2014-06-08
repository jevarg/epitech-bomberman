#include "GameEngine.hpp"
#include "StockItem.hpp"

StockItem::StockItem(int x, int y, t_gameinfo *gameInfo, bool thread) :
  AItem(x, y, STOCKITEM, gameInfo, thread)
{
  _amount = HEALTH_AMOUNT;
}

StockItem::~StockItem()
{
}

void	StockItem::setAttr(ACharacter *ch) const
{
  ch->setBombStock(ch->getBombStock() + _amount);
  // _gameInfo->sound->playSound("eat");
}

AItem	*StockItem::clone(int x, int y)
{
  return (new StockItem(x, y, _gameInfo));
}
