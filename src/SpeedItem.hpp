#ifndef _SPEEDITEM_H_
# define _SPEEDITEM_H_

# include "AItem.hpp"

class SpeedItem : public AItem
{
public:
  SpeedItem();
  virtual ~SpeedItem();

  void	setSpeed(ACharacter &ch) const;
};

#endif /* _SPEEDITEM_H_ */
