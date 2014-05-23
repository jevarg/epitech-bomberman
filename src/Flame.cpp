#include "GameEngine.hpp"
#include "Flame.hpp"

Flame::Flame(int x, int y, int power, int range, eDir direction, t_gameinfo &gameInfo)
  : ALivingEntity(x, y, FLAME, gameInfo)
{
  _power = power;
  _range = range;
  _direction = direction;
  _timeout = 3 * _gameInfo.set.getVar(FPS);
  _nextFlame = 1000 / (1000 / _gameInfo.set.getVar(FPS)); // first nb = delay in ms
}

Flame::~Flame()
{
}

void	Flame::update()
{
  if ((--_timeout) == 0)
    {
      _toDestroy = true;
      return ;
    }
  if ((--_nextFlame) == 0 && _range >= 0)
    {
      switch (_direction)
	{
	case ALLDIR:
	  setFire(_x, _y - 1, NORTH);
	  setFire(_x, _y + 1, SOUTH);
	  setFire(_x - 1, _y, WEST);
	  setFire(_x + 1, _y, EAST);
	  break;
	case NORTH:
	  setFire(_x, _y - 1, NORTH);
	  break;
	case SOUTH:
	  setFire(_x, _y + 1, SOUTH);
	  break;
	case WEST:
	  setFire(_x - 1, _y, WEST);
	  break;
	case EAST:
	  setFire(_x + 1, _y, EAST);
	  break;
	}
    }
}

void    Flame::setFire(int x, int y, eDir direction)
{
  Flame		*newFlame;
  AEntity	*character;
  AEntity	*object;
  bool		hit = false;

  if (_gameInfo.map.getEntityIf(x, y, WALL) != NULL)
    {
      std::cout << "hit wall" << std::endl;
      return ;
    }
  else
    {
      if ((character = _gameInfo.map.getEntityIf(x, y, CHARACTER)) != NULL)
	{
	  character->takeDamages(_power);
	  hit = true;
	}
      if ((object = _gameInfo.map.getEntityIfNot(x, y, CHARACTER)) != NULL)
	{
	  object->takeDamages(_power);
	  hit = true;
	}
    }
  if (hit == false)
    {
      newFlame = new Flame(x, y, _power, _range - 1, direction, _gameInfo);
      _gameInfo.map.addEntity(newFlame);
    }
}

void	Flame::hurtCharacter(ACharacter *character, int power)
{
  character->takeDamages(power);
}
