#include "Condvar.hpp"

Condvar::Condvar()
{
  pthread_cond_init(&_cond, NULL);
}

Condvar::~Condvar()
{
  pthread_cond_destroy(&_cond);
}

void	Condvar::wait(pthread_mutex_t *mutex)
{
  pthread_cond_wait(&_cond, mutex);
}

void	Condvar::signal()
{
  pthread_cond_signal(&_cond);
}

void	Condvar::broadcast()
{
  pthread_cond_broadcast(&_cond);
}
