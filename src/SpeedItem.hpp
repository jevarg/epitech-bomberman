#ifndef _SPEEDITEM_H_
# define _SPEEDITEM_H_

# include "AItem.hpp"

class SpeedItem : public AItem
{
public:
  SpeedItem(int x, int y, eType type, t_gameinfo &gameInfo);
  virtual ~SpeedItem();

  void	setAttr(ACharacter *ch) const;
};

#endif /* _SPEEDITEM_H_ */
