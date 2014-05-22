#include "GameEngine.hpp"
#include "Flame.hpp"

Flame::Flame(int x, int y, int power, eDir direction, t_gameinfo &gameInfo)
  : ALivingEntity(x, y, FLAME, gameInfo)
{
  _power = power;
}

Flame::~Flame()
{
}

/* If bomb doesn't work, think about modifying entity setters (used here) */
void    Flame::setFire(int x, int y, eDir direction, int range)
{
  Flame *newFlame;

  if (_gameInfo.map.getEntityIf(x, y, WALL))
    return ;
  if (direction != ALLDIR)
    {
      newFlame = new Flame(x, y, _power, ALLDIR, _gameInfo);
      _gameInfo.map.addEntity(newFlame);
    }
  if (_gameInfo.map.getEntityIf(x, y, CHARACTER))
    {
      hurtCharacter((ACharacter *)_gameInfo.map.getEntityIf(x, y, CHARACTER), _power);
      return ;
    }
  else if (_gameInfo.map.getEntityIfNot(x, y, CHARACTER))
    {
      _gameInfo.map.setEntity(x, y, FREE);
      return ;
    }
  if (range > 0)
    {
      switch (direction)
	{
	case ALLDIR: // used "this" here to be explicit between each case //
	  this->setFire(x, y - 1, NORTH, range - 1);
	  this->setFire(x, y + 1, SOUTH, range - 1);
	  this->setFire(x - 1, y, WEST, range - 1);
	  this->setFire(x + 1, y, EAST, range - 1);
	  break;
	case NORTH:
	  newFlame->setFire(x, y - 1, NORTH, range - 1);
	  break;
	case SOUTH:
	  newFlame->setFire(x, y + 1, SOUTH, range - 1);
	  break;
	case WEST:
	  newFlame->setFire(x - 1, y, WEST, range - 1);
	  break;
	case EAST:
	  newFlame->setFire(x + 1, y, EAST, range - 1);
	  break;
	default:
	  break;
	}
    }
}

void	Flame::hurtCharacter(ACharacter *character, int power)
{
  character->setHealth(character->getHealth() - power);
}

void	Flame::update()
{
}
