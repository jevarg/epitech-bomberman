#include "Bomb.hpp"
#include "Exception.hpp"

Bomb::Bomb()
  : _mutex()
{
  pthread_t         thread;

  if (pthread_create(&thread, NULL, &handle_bomb_thread, this) != 0)
    throw (Exception("Can't create Bomb's thread"));
  _thread = thread;
}

Bomb::~Bomb()
{
}

void	*handle_bomb_thread(void *arg)
{
  (void) arg;
  return (NULL);
}
