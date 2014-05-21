#ifndef ABOMB_HPP_
# define ABOMB_HPP_

# include "ALivingEntity.hpp"
# include "IObject.hpp"
# include "Settings.hpp"

class		ABomb: public ALivingEntity
{
public:
  ABomb(int x, int y, IObject *model, t_gameinfo &gameInfo);
  virtual ~ABomb();
  void	explode(Map &map);
  void	setFire(int x, int y, eAction direction, int range, Map &map);
  virtual void	update(t_gameinfo &gameInfo) = 0;

protected:
  int		_range;
  int		_power;
};

#endif /* ! BOMB_HPP_ */
