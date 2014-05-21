#ifndef FLAME_HPP_
# define FLAME_HPP_

# include "AEntity.hpp"
# include "ACharacter.hpp"

class	Flame : public ALivingEntity
{
private:
  Mutex		_mutex;
  Condvar	_condvar;

public:
  Flame(int x, int y, t_gameinfo &gameInfo);
  ~Flame();
  void	hurtCharacter(ACharacter *character);
  void	update(t_gameinfo &gameInfo);
};

#endif /* !FLAME_HPP_ */
