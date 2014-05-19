#ifndef _AITEM_HPP_
# define _AITEM_HPP_

# include "AEntity.hpp"
# include "ACharacter.hpp"

# define NO_TIMEOUT -10
enum
  {
    SPEED_AMOUNT = 1,
    HEALTH_AMOUNT = 20
  };

class AItem
{
public:
  AItem();
  virtual ~AItem();

protected:
  int	_timeout;
  int	_amount;
};

#endif /* _AITEM_HPP_ */
