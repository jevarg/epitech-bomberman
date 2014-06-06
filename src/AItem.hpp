#ifndef _AITEM_HPP_
# define _AITEM_HPP_

# include "ALivingEntity.hpp"
# include "ACharacter.hpp"

# define NO_TIMEOUT -10

enum
  {
    SPEED_AMOUNT = 1,
    SPEED_MAX = 15,
    HEALTH_AMOUNT = 1,
    HEALTH_MAX = 3
  };

class AItem : public ALivingEntity
{
public:
  AItem(int x, int y, eType type, t_gameinfo *gameInfo);
  virtual ~AItem() = 0;

  void	update();
  bool	checkItemColision(const Map *map);

  virtual void	setAttr(ACharacter *ch) const = 0;
  virtual AItem	*clone(int x, int y) = 0;
protected:
  int	_timeout;
  int	_amount;
};

#endif /* _AITEM_HPP_ */
