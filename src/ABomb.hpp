#ifndef ABOMB_HPP_
# define ABOMB_HPP_

# include "AEntity.hpp"
# include "IObject.hpp"
# include "Mutex.hpp"
# include "Condvar.hpp"
# include "Settings.hpp"

class		ABomb: public AEntity
{
public:
  ABomb(int x, int y, IObject *model);
  virtual ~ABomb();
  void	explode(Map &map);
  void	setFire(int x, int y, eAction direction, int range, Map &map);

protected:
  pthread_t	_thread;
  Mutex		_mutex;
  Condvar	_condvar;
  int		_range;
  int		_power;
};

void	*handle_bomb_thread(void *arg);

#endif /* ! BOMB_HPP_ */
