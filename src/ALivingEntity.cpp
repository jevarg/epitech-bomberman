#include "GameEngine.hpp"
#include "ALivingEntity.hpp"

ALivingEntity::ALivingEntity(int x, int y, eType type,
			     IObject *model, t_gameinfo &gameInfo) :
  AEntity(x, y, type, model), _gameInfo(gameInfo)
{
  if (pthread_create(&_thread, NULL, &createAliveEntity, NULL) != 0)
    throw (Exception("Can't create thread"));
}

ALivingEntity::~ALivingEntity()
{
}

void	*ALivingEntity::createAliveEntity(void *arg)
{
  (void)arg;
  //aliveLoop()
  return (NULL);
}

void	ALivingEntity::aliveLoop()
{
  while (1)
    {
      //update()
    }
}

bool	ALivingEntity::isAlive() const
{
  return (_isAlive);
}
