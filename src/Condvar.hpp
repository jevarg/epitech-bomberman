#ifndef _CONDVAR_HPP_
# define _CONDVAR_HPP_

# include <pthread.h>

class Condvar
{
public:
  Condvar();
  ~Condvar();

  void	wait(pthread_mutex_t *mutex);
  void	signal();
  void	broadcast();

private:
  pthread_cond_t	_cond;
};

#endif /* _CONDVAR_HPP_ */
