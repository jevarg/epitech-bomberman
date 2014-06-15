#include "GameEngine.hpp"
#include "ALivingEntity.hpp"

ALivingEntity::ALivingEntity(int x, int y, eType type, t_gameinfo *gameInfo, bool thread) :
  AEntity(x, y, type, gameInfo)
{
  _timeDeath = gameInfo->set->getVar(FPS) + 10; // need to overload considering the collector
  _isAlive = true;
  if (thread)
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

bool	ALivingEntity::die()
{
  Scopelock	<Mutex>sc(*_mutex);

  if (_isAlive == false)	// just because it's not usefull iterating through
    return (false);    		// all the containers
  _isAlive = false;
  _gameInfo->map->removeEntityByPtr(this);
  return (true);
}

void	ALivingEntity::setDestroy()
{
  die();
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
      _gameInfo->mutex->lock();
      _gameInfo->condvar->wait(_gameInfo->mutex->getMutexPtr());
      _gameInfo->mutex->unlock();
      if (_isAlive)
	update();
      else if (_type != CHARACTER1 && _type != CHARACTER2)
	{
	  if ((_timeDeath =- 1) <= 0)
	    destroy();
	}
      if (_toDestroy)
	destroy();
    }
}

bool	ALivingEntity::isAlive() const
{
  return (_isAlive);
}

void	ALivingEntity::takeDamages(int /*amount*/)
{
  die();
}

void	ALivingEntity::setDestroyAttr()
{
  _toDestroy = true;
  _isAlive = false;
}
