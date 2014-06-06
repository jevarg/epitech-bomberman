#ifndef FLAME_HPP_
# define FLAME_HPP_

# include "ALivingEntity.hpp"
# include "ACharacter.hpp"

class	Flame : public ALivingEntity
{
private:
  int	_power;
  int	_range;
  eDir	_direction;
  int	_timeout;
  int	_nextFlame;

public:
  Flame(int x, int y, int power, int range, eDir direction, t_gameinfo *gameInfo);
  ~Flame();
  void	setFire(int x, int y, eDir direction);
  void	hurtCharacter(ACharacter *character, int power);
  void	update();
};

#endif /* !FLAME_HPP_ */
