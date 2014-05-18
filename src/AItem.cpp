#include "AItem.hpp"

AItem::AItem()
{
}

AItem::~AItem()
{
}

void	AItem::modifyAmount(int &objAttr)
{
  objAttr += _powerAmount;
  if (objAttr < 0)
    objAttr = 0;
}
