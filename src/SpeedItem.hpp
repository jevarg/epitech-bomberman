#ifndef _SPEEDITEM_H_
# define _SPEEDITEM_H_

# include "AItem.hpp"

class SpeedItem : public AItem
{
public:
  SpeedItem(int x, int y, t_gameinfo *gameInfo, bool thread = true);
  virtual ~SpeedItem();

  void	setAttr(ACharacter *ch) const;
  AItem	*clone(int x, int y);
};

#endif /* _SPEEDITEM_H_ */
