#ifndef _HEALTHITEM_H_
# define _HEALTHITEM_H_

# include "AItem.hpp"

class HealthItem : public AItem
{
public:
  HealthItem(int x, int y, eType type, t_gameinfo &gameInfo);
  virtual ~HealthItem();

  void	setAttr(ACharacter *ch) const;
};

#endif /* _HEALTHITEM_H_ */
