#include "Map.hpp"
#include "Input.hpp"
#include "ACharacter.hpp"

ACharacter::ACharacter(int x, int y, glm::vec4 color, IObject *model)
  : AEntity(x, y, CHARACTER, model), _mutex(), _condvar(), _color(color),
    _health(1), _isAlive(true), _bombStock(1),
    _bombType(NORMAL), _speed(5), _range(5), _score(0), _orient(NORTH)
{
  pthread_t         thread;

  if (pthread_create(&thread, NULL, &handle_thread, this) != 0)
    throw (Exception("Can't create Acharacter's thread"));
  _thread = thread;
}

ACharacter::~ACharacter()
{
}

void	ACharacter::move(eAction action, Map &map)
{
  switch (action)
    {
    case FORWARD:
      if (map.checkMapColision(_x, _y + 1) == FREE)
	{
	  _y += 1;
	  map.setMobilEnt(_x, _y, CHARACTER);
	  map.setMobilEnt(_x, _y - 1, FREE);
	  _model->translate(glm::vec3(0, 0, 1));
	  _model->rotate(glm::vec3(0.0, 1.0, 0.0), 90.0 * NORTH - 90.0 * _orient);
	  _orient = NORTH;
	}
      break;
    case BACK:
      if (map.checkMapColision(_x, _y - 1) == FREE)
	{
	  _y -= 1;
	  map.setMobilEnt(_x, _y, CHARACTER);
	  map.setMobilEnt(_x, _y + 1, FREE);
	  _model->translate(glm::vec3(0, 0, -1));
	  _model->rotate(glm::vec3(0.0, 1.0, 0.0), 90.0 * SOUTH - 90.0 * _orient);
	  _orient = SOUTH;
	}
      break;
    case LEFT:
      if (map.checkMapColision(_x + 1, _y) == FREE)
	{
	  _x += 1;
	  map.setMobilEnt(_x, _y, CHARACTER);
	  map.setMobilEnt(_x - 1, _y, FREE);
	  _model->translate(glm::vec3(1, 0, 0));
	  _model->rotate(glm::vec3(0.0, 1.0, 0.0), 90.0 * WEST - 90.0 * _orient);
	  _orient = WEST;
	}
      break;
    case RIGHT:
      if (map.checkMapColision(_x - 1, _y) == FREE)
	{
	  _x -= 1;
	  map.setMobilEnt(_x, _y, CHARACTER);
	  map.setMobilEnt(_x + 1, _y, FREE);
	  _model->translate(glm::vec3(-1, 0, 0));
	  _model->rotate(glm::vec3(0.0, 1.0, 0.0), 90.0 * EAST - 90.0 * _orient);
	  _orient = EAST;
	}
      break;
    default:
      break;
    }
}

void	ACharacter::hit()
{
  --_health;
  if (_health == 0)
    _isAlive = false;
}

bool	ACharacter::initialize()
{
  return (true);
}

int	ACharacter::getScore() const
{
  return (_score);
}

bool	ACharacter::isAlive() const
{
  return (_isAlive);
}

void	*handle_thread(void *arg)
{
  (void) arg;
  return (NULL);
}
