#ifndef FLAME_HPP_
# define FLAME_HPP_

# include "AEntity.hpp"
# include "ACharacter.hpp"

class	Flame : public AEntity
{
private:
  Mutex		_mutex;
  Condvar	_condvar;

public:
  Flame(int x, int y, IObject *model);
  ~Flame();
  void	hurtCharacter(ACharacter *character);
  void	update(t_gameinfo &gameInfo);
};

#endif /* !FLAME_HPP_ */
