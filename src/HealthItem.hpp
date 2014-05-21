#ifndef _HEALTHITEM_H_
# define _HEALTHITEM_H_

# include "AItem.hpp"

class SpeedItem : public AItem
{
public:
  SpeedItem();
  virtual ~SpeedItem();

  void	setHealth(ACharacter &ch);
};

#endif /* _HEALTHITEM_H_ */
