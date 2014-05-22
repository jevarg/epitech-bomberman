#include "GameEngine.hpp"
#include "ALivingEntity.hpp"

ALivingEntity::ALivingEntity(int x, int y, eType type, t_gameinfo &gameInfo) :
  AEntity(x, y, type, gameInfo)
{
  _isAlive = true;

  if (pthread_create(&_thread, NULL, &createAliveEntity, this) != 0)
    throw (Exception("Can't create thread"));
}

ALivingEntity::~ALivingEntity()
{
}

void	ALivingEntity::setDead()
{
  _isAlive = false;
}

void	*createAliveEntity(void *arg)
{
  static_cast<ALivingEntity *>(arg)->aliveLoop();
  return (NULL);
}

void	ALivingEntity::destroy(Map &map)
{
  map.removeEntityByPtr(this);
  delete (this);
  pthread_exit(NULL);
}

void	ALivingEntity::aliveLoop()
{
  while (1)
    {
      _gameInfo.mutex->lock();
      _gameInfo.condvar->wait(_gameInfo.mutex->getMutexPtr());
      _gameInfo.mutex->unlock();
      if (_toDestroy)
	destroy(_gameInfo.map);
      if (_isAlive)
	update();
    }
  pthread_exit(NULL);
}

bool	ALivingEntity::isAlive() const
{
  return (_isAlive);
}

void	ALivingEntity::die()
{
  delete(this);
}

void	ALivingEntity::takeDamages(int /*amount*/)
{
  _toDestroy = true;
}
