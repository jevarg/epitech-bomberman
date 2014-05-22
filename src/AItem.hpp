#ifndef _AITEM_HPP_
# define _AITEM_HPP_

# include "ALivingEntity.hpp"
# include "ACharacter.hpp"

# define NO_TIMEOUT -10
enum
  {
    SPEED_AMOUNT = 1,
    HEALTH_AMOUNT = 20
  };

class AItem : public ALivingEntity
{
public:
  AItem(int x, int y, eType type, t_gameinfo &gameInfo);
  virtual ~AItem() = 0;

  void	update(t_gameinfo &gameInfo);
  void	takeDamages(int amount);
  void	destroy(Map &map);
protected:
  int	_timeout;
  int	_amount;
};

#endif /* _AITEM_HPP_ */
