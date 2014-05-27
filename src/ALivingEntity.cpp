#include "GameEngine.hpp"
#include "ALivingEntity.hpp"

ALivingEntity::ALivingEntity(int x, int y, eType type, t_gameinfo &gameInfo) :
  AEntity(x, y, type, gameInfo)
{
  _isAlive = true;
  _mutex = new Mutex;
  if (pthread_create(&_thread, NULL, &createAliveEntity, this) != 0)
    throw (Exception("Can't create thread"));
  _timedeath = gameInfo.set.getVar(FPS); // set to one second
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

void	ALivingEntity::die()
{
  Scopelock	<Mutex>sc(*_mutex);

  if (_isAlive == false)	// just because it's not usefull iterating through
    return ;			// all the containers
  _isAlive = false;
  _gameInfo.map.removeEntityByPtr(this);
}

void	ALivingEntity::destroy()
{
  delete (_mutex);
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
      if (_isAlive)
	update();
      else
	{
	  if ((_timedeath =- 1) <= 0)
	    destroy();
	}
    }
}

bool	ALivingEntity::isAlive() const
{
  return (_isAlive);
}

void	ALivingEntity::takeDamages(int /*amount*/)
{
  if (_isAlive == false)
    return ;
  die();
}
