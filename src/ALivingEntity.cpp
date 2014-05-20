#include "ALivingEntity.hpp"

ALivingEntity::ALivingEntity(int x, int y, eType type,
			     IObject *model, Condvar &condvar, Mutex &mutex) :
  AEntity(x, y, type, model), _mutex(mutex), _condvar(condvar)
{
}

ALivingEntity::~ALivingEntity()
{
}

void	*ALivingEntity::createAliveEntity(void *arg)
{
  (void)arg;
  return (NULL);
}

void	ALivingEntity::aliveLoop()
{
}

bool	ALivingEntity::isAlive() const
{
  return (_isAlive);
}
