#include "GameEngine.hpp"
#include "Map.hpp"
#include "Input.hpp"
#include "ACharacter.hpp"

ACharacter::ACharacter(int x, int y, glm::vec4 color, t_gameinfo &gameInfo)
  : ALivingEntity(x, y, CHARACTER, gameInfo)
/* handle the bomb type at creation */
{
  _bombStock = 1;
  _health = 1;
  _speed = 5;
  _range = 5;
  _score = 0;
  _orient = NORTH;
  _anim = NOTHING;
  _color = color;
  _x += 0.5;
  _y += 0.5;
  _model->translate(glm::vec3(0.0, -0.5, 0.0));
  _model->scale(glm::vec3(0.5, 0.5, 0.5));
}

ACharacter::~ACharacter()
{
  std::cout << "ACharacter death" << std::endl;
}

bool	ACharacter::updatePosition(Map &map, eAction action, const gdl::Clock &clock)
{
  eAction	tab[4] = {FORWARD, BACK, LEFT, RIGHT};
  eDir		tabdir[4] = {SOUTH, NORTH, EAST, WEST};
  float		dirX;
  float		dirY;
  int		colisionType;
  float		movement;

  for (int i = 0; i < 4; ++i)
    {
      if (tab[i] == action)
	{
	  movement = clock.getElapsed() * static_cast<float>(_speed);
	  dirX = ((i >= 2) ? ((action == LEFT) ? -movement : movement) : 0);
	  dirY = ((i < 2) ? ((action == FORWARD) ? -movement : movement) : 0);
	  _model->rotate(glm::vec3(0.0, 1.0, 0.0), 90.0 * tabdir[i] - 90.0 * _orient);
	  _orient = tabdir[i];
	  switch ((colisionType = map.checkMapColision(_x + dirX,
						       _y + dirY)))
	    {
	    case CHARACTER:
	    case FREE:
	    case SPEEDITEM:
	    case HEALTHITEM:
	      if (_anim == NOTHING)
	      	{
		  dynamic_cast<Model *>(_model)->getModel()->setCurrentAnim(0, true);
		  _anim = RUN;
		}
	      return (move(map, dirX, dirY));
	      break;
	    default:
	      break;
	    }
	  break ;
	}
    }
  return (false);
}

bool	ACharacter::move(Map &map, float dirX, float dirY)
{
  unsigned int oldCont;
  unsigned int newCont;

  _model->translate(glm::vec3(dirX, 0.0, dirY));
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

void	ACharacter::dropBomb()
{
  if (_gameInfo.map.getEntityIfNot(_x, _y, CHARACTER) == NULL && _bombStock > 0)
    {
      --(_bombStock);
      _gameInfo.map.addEntity(new Bomb(_x, _y, this, _gameInfo));
      std::cout << "Will drop bomb at pos: " << _x << " " << _y << std::endl;
    }
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

void	ACharacter::setSpeed(int speed)
{
  _speed = speed;
}

void	ACharacter::takeDamages(int amount)
{
  _health -= amount;
  if (_health <= 0)
    die();
}
int	ACharacter::getHealth() const
{
  return (_health);
}

void	ACharacter::setHealth(int health)
{
  _health = health;
  if (_health <= 0)
    die();
}

int	ACharacter::getBombStock() const
{
  return (_bombStock);
}

void	ACharacter::setBombStock(int bombStock)
{
  _bombStock = bombStock;
}

ABomb	*ACharacter::getBomb() const
{
  return (_bomb);
}

void	ACharacter::setBomb(ABomb *bomb)
{
  _bomb = bomb;
}
int	ACharacter::getRange() const
{
  return (_range);
}

void	ACharacter::setRange(int range)
{
  _range = range;
}
