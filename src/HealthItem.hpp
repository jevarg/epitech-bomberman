#ifndef _HEALTHITEM_H_
# define _HEALTHITEM_H_

# include "AItem.hpp"

class HealthItem : public AItem
{
public:
  HealthItem(int x, int y, t_gameinfo *gameInfo, bool thread = true);
  virtual ~HealthItem();

  void	setAttr(ACharacter *ch) const;
  AItem	*clone(int x, int y);
};

#endif /* _HEALTHITEM_H_ */
