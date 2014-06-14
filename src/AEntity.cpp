#include "GameEngine.hpp"
#include "Map.hpp"
#include "AEntity.hpp"

AEntity::AEntity(t_gameinfo *gameInfo) : _gameInfo(gameInfo)
{
  _toDestroy = false;
  _timeDeath = gameInfo->set->getVar(FPS); // set to one second
  _mutex = new Mutex;
}

AEntity::AEntity(int x, int y, eType type, t_gameinfo *gameInfo) :
  _type(type), _gameInfo(gameInfo)
{
  _toDestroy = false;
  _model = ModelFactory::getInstance().getModel(_type);
  _x = static_cast<float>(x);
  _y = static_cast<float>(y);
  _model->translate(glm::vec3(x, 0.0, y));
  _timeDeath = gameInfo->set->getVar(FPS); // set to one second
  _mutex = new Mutex;
}

AEntity::~AEntity()
{
}

int	AEntity::getXPos() const
{
  return (_x);
}

int	AEntity::getYPos() const
{
  return (_y);
}

eType	AEntity::getType() const
{
  return (_type);
}

void	AEntity::setXPos(const int &x)
{
  _x = x;
}

void	AEntity::setYPos(const int &y)
{
  _y = y;
}

void	AEntity::setType(const eType &type)
{
  _type = type;
}

bool	AEntity::toDestroy() const
{
  return (_toDestroy);
}

void	AEntity::setDestroy()
{
  Scopelock	<Mutex>sc(*_mutex);

  if (_toDestroy == true)
    return ;
  _toDestroy = true;
  _gameInfo->map->pushToCollector(this);
  _gameInfo->map->removeEntityByPtr(this);
}

void	AEntity::draw(gdl::AShader &shader, gdl::Clock &clock)
{
  _model->draw(shader, clock);
}

int	AEntity::getDeathTime() const
{
  return (_timeDeath);
}

void	AEntity::decTimeDeath()
{
  --_timeDeath;
}

void	AEntity::destroy()
{
  delete (_mutex);
  delete (this);
}

IObject *AEntity::getModel() const
{
  return (_model);
}
