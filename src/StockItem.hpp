#ifndef _STOCKITEM_H_
#define _STOCKITEM_H_

# include "AItem.hpp"

class StockItem : public AItem
{
public:
  StockItem(int x, int y, t_gameinfo *gameInfo, bool thread = true);
  virtual ~StockItem();

  void	setAttr(ACharacter *ch) const;
  AItem	*clone(int x, int y);
};

#endif /* _STOCKITEM_H_ */
