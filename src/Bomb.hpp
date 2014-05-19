#ifndef BOMB_HPP_
# define BOMB_HPP_

# include "Mutex.hpp"
# include "Condvar.hpp"

enum	eBombType
  {
    NORMAL,
    BONUS
  };

class		Bomb
{
public:
  Bomb();
  ~Bomb();

private:
  pthread_t	_thread;
  Mutex		_mutex;
  Condvar	_condvar;
  eBombType	_type;
  int		_range;
};

void	*handle_bomb_thread(void *arg);

#endif /* ! BOMB_HPP_ */
