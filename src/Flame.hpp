#ifndef FLAME_HPP_
# define FLAME_HPP_

# include "ALivingEntity.hpp"
# include "ACharacter.hpp"

class	Flame : public ALivingEntity
{
private:
  int	_power;

public:
  Flame(int x, int y, int power, eDir direction, t_gameinfo &gameInfo);
  ~Flame();
  void	setFire(int x, int y, eDir direction, int range);
  void	hurtCharacter(ACharacter *character, int power);
  void	update();
};
#endif /* !FLAME_HPP_ */
