#ifndef _RANGEITEM_H_
# define _RANGEITEM_H_

# include "AItem.hpp"

class RangeItem : public AItem
{
public:
  RangeItem(int x, int y, t_gameinfo *gameInfo, bool thread = true);
  virtual ~RangeItem();

  void	setAttr(ACharacter *ch) const;
  AItem	*clone(int x, int y);
};


#endif /* _RANGEITEM_H_ */
