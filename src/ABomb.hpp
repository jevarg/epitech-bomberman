#ifndef ABOMB_HPP_
# define ABOMB_HPP_

# include "ALivingEntity.hpp"
# include "IObject.hpp"
# include "Settings.hpp"

class		ABomb: public ALivingEntity
{
public:
  ABomb(int x, int y, t_gameinfo &gameInfo);
  virtual ~ABomb();

  void	explode(Map &map);
  void	takeDamages(int);

  virtual void	update(t_gameinfo &gameInfo) = 0;

protected:
  int		_range;
  int		_power;
};

#endif /* ! BOMB_HPP_ */
