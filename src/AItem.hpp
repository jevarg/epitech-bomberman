#ifndef _AITEM_HPP_
# define _AITEM_HPP_

# include "ALivingEntity.hpp"
# include "ACharacter.hpp"

# define NO_TIMEOUT -10
# define ITEM_SCORE 20

class AItem : public ALivingEntity
{
public:
  AItem(int x, int y, eType type, t_gameinfo *gameInfo, bool thread = true);
  virtual ~AItem() = 0;

  void	update();
  bool	checkItemColision(const Map *map);

  void	increaseScore(ACharacter *character) const;

  virtual void	setAttr(ACharacter *ch) const = 0;
  virtual AItem	*clone(int x, int y) = 0;
protected:
  int	_timeout;
  int	_amount;
};

#endif /* _AITEM_HPP_ */
