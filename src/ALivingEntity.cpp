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
  _gameInfo.map.removeEntityByPtr(this);
  _isAlive = false;
}

void	ALivingEntity::destroy()
{
  _mutex->unlock();
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
      _mutex->lock();
      if (_isAlive)
	update();
      else
	{
	  if ((_timedeath =- 1) <= 0)
	    destroy();
	}
      _mutex->unlock();
    }
}

bool	ALivingEntity::isAlive() const
{
  return (_isAlive);
}

void	ALivingEntity::takeDamages(int /*amount*/)
{
  _mutex->lock();
  if (_isAlive == false)
    return ;
  die();
  _mutex->unlock();
}
