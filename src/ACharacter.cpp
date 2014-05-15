#include "Map.hpp"
#include "Input.hpp"
#include "ACharacter.hpp"

ACharacter::ACharacter(int x, int y, glm::vec4 color, IObject *model)
  : AEntity(x, y, CHARACTER, model), _mutex(), _condvar(), _color(color),
    _health(1), _isAlive(true), _bombStock(1),
    _bombType(NORMAL), _speed(5), _range(5), _score(0)
{
  pthread_t         thread;

  if (pthread_create(&thread, NULL, &handle_character_thread, this) != 0)
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
	  _model->translate(glm::vec3(0, 0, 2));

	}
      break;
    case BACK:
      if (map.checkMapColision(_x, _y - 1) == FREE)
	{
	  _y -= 1;
	  map.setMobilEnt(_x, _y, CHARACTER);	  
	  map.setMobilEnt(_x, _y + 1, FREE);
	  _model->translate(glm::vec3(0, 0, -2));
	}
      break;
    case LEFT:
      if (map.checkMapColision(_x + 1, _y) == FREE)
	{
	  _x += 1;
	  map.setMobilEnt(_x, _y, CHARACTER);	  
	  map.setMobilEnt(_x - 1, _y, FREE);
	  _model->translate(glm::vec3(2, 0, 0));
	}
      break;
    case RIGHT:
      if (map.checkMapColision(_x - 1, _y) == FREE)
	{
	  _x -= 1;
	  map.setMobilEnt(_x, _y, CHARACTER);	  
	  map.setMobilEnt(_x + 1, _y, FREE);
	  _model->translate(glm::vec3(-2, 0, 0));
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

void	*handle_character_thread(void *arg)
{
  (void) arg;
  return (NULL);
}
