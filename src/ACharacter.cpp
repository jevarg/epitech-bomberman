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

void	ACharacter::updatePosition(Map &map, eAction action)
{
  eAction	tab[4] = {FORWARD, BACK, LEFT, RIGHT};
  int		dirX;
  int		dirY;

  for (int i = 0; i < 4; ++i)
    {
      if (tab[i] == action)
	{
	  dirX = ((i >= 2) ? ((action == LEFT) ? 1 : -1) : 0);
	  dirY = ((i < 2) ? ((action == FORWARD) ? 1 : -1) : 0);
	  if (map.checkMapColision(_x + dirX, _y + dirY) == FREE)
	    {
	      move(map, dirX, dirY);
	      _model->translate(glm::vec3(dirX * 2, 0, dirY * 2));
	    }
	  break ;
	}
    }
}

void	ACharacter::move(Map &map, int dirX, int dirY)
{
  (void)map;
  // HERE CHECK CONTAINER CHANGEMENT
  _y += dirY;
  _x += dirX;
}

void	ACharacter::takeDamages(int amount)
{
  _health -= amount;
  if (_health <= 0)
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
