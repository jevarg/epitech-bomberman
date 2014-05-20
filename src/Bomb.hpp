#ifndef BOMB_HPP_
# define BOMB_HPP_

# include "ABomb.hpp"
# include "IObject.hpp"

class		Bomb: public ABomb
{
public:
  Bomb(int x, int y, IObject *model);
  virtual ~Bomb();

private:
  pthread_t	_thread;
  Mutex		_mutex;
  int		_range;
};

#endif /* ! BOMB_HPP_ */
