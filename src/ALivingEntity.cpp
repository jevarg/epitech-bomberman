#include "GameEngine.hpp"
#include "ALivingEntity.hpp"

ALivingEntity::ALivingEntity(int x, int y, eType type,
			     IObject *model, t_gameinfo &gameInfo) :
  AEntity(x, y, type, model), _gameInfo(gameInfo)
{
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

void	ALivingEntity::aliveLoop()
{
  while (1)
    {
      if (_toDestroy)
	{
	  int	ret;
	  pthread_exit(&ret);
	  //delete this;
	  break ;
	}
      if (_isAlive)
	update(_gameInfo);
    }
  pthread_exit(NULL);
}

bool	ALivingEntity::isAlive() const
{
  return (_isAlive);
}
