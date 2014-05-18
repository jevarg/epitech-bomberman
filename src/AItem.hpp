#ifndef _AITEM_HPP_
# define _AITEM_HPP_

# include "AEntity.hpp"

# define NO_TIMEOUT -10

class AItem
{
public:
  AItem();
  virtual ~AItem();

  void	modifyAmount(int &objAttr);

protected:
  int	_timeout;
  int	_powerAmount;
};

#endif /* _AITEM_HPP_ */
