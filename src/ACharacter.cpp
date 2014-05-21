#include "Map.hpp"
#include "Input.hpp"
#include "ACharacter.hpp"

ACharacter::ACharacter(int x, int y, glm::vec4 color, t_gameinfo &gameInfo)
  : ALivingEntity(x, y, CHARACTER, gameInfo)
/* handle the bomb type at creation */
{
  _bombStock = 1;
  _health = 100;
  _speed = 5;
  _range = 5;
  _score = 0;
  _orient = NORTH;
  _color = color;
  _model->translate(glm::vec3(0.0, -0.5, 0.0));
  _model->scale(glm::vec3(0.002, 0.002, 0.002));
}

ACharacter::~ACharacter()
{
  std::cout << "ACharacter death" << std::endl;
}

bool	ACharacter::updatePosition(Map &map, eAction action)
{
  eAction	tab[4] = {FORWARD, BACK, LEFT, RIGHT};
  eDir		tabdir[4] = {NORTH, SOUTH, WEST, EAST};
  int		dirX;
  int		dirY;

  for (int i = 0; i < 4; ++i)
    {
      if (tab[i] == action)
	{
	  dirX = ((i >= 2) ? ((action == LEFT) ? 1 : -1) : 0);
	  dirY = ((i < 2) ? ((action == FORWARD) ? 1 : -1) : 0);
	  _model->rotate(glm::vec3(0.0, 1.0, 0.0), 90.0 * tabdir[i] - 90.0 * _orient);
	  _orient = tabdir[i];
	  if (map.checkMapColision(_x + dirX, _y + dirY) == FREE)
	    {
	      _model->translate(glm::vec3(dirX, 0, dirY));
	      return (move(map, dirX, dirY));
	    }
	  break ;
	}
    }
  return (false);
}

bool	ACharacter::move(Map &map, int dirX, int dirY)
{
  unsigned int oldCont;
  unsigned int newCont;

  oldCont = map.getContPos(_x, _y);
  newCont = map.getContPos(_x + dirX, _y + dirY);
  if (newCont != oldCont) // means the player crossed from contA to contB
    {
      std::cout << "Remove element at old pos" << std::endl;
      map.removeEntityByPtr(this);
    }
  _y += dirY;
  _x += dirX;
  if (newCont != oldCont) // now add it to contB
    {
      std::cout << "Add it at new pos" << std::endl;
      map.addEntity(this);
    }
  return (true);
}

bool	ACharacter::initialize()
{
  return (true);
}

int	ACharacter::getScore() const
{
  return (_score);
}

void	*handle_character_thread(void *arg)
{
  (void) arg;
  return (NULL);
}

int	ACharacter::getSpeed() const
{
  return (_speed);
}

int	ACharacter::getHealth() const
{
  return (_health);
}

void	ACharacter::setSpeed(int speed)
{
  _speed = speed;
}

void	ACharacter::setHealth(int health)
{
  _health = health;
  if (_health <= 0)
    _isAlive = false;
}
