#include "GameEngine.hpp"
#include "Flame.hpp"

Flame::Flame(int x, int y, int power, int range, eDir direction, t_gameinfo &gameInfo)
  : ALivingEntity(x, y, FLAME, gameInfo)
{
  _power = power;
  _range = range;
  _direction = direction;
  _timeout = 1 * _gameInfo.set.getVar(FPS);
  _nextFlame = 100 / (1000 / _gameInfo.set.getVar(FPS)); // first nb = delay in ms
}

Flame::~Flame()
{
}

void	Flame::update()
{
  if (--_timeout == 0)
    this->destroy(_gameInfo.map);
  if (--_nextFlame == 0)
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
	case SOUTH:
	  setFire(_x, _y + 1, SOUTH);
	case WEST:
	  setFire(_x - 1, _y, WEST);
	case EAST:
	  setFire(_x + 1, _y, EAST);
	}
    }
}

void    Flame::setFire(int x, int y, eDir direction)
{
  Flame		*newFlame;
  AEntity	*character;
  AEntity	*object;

  if (_gameInfo.map.getEntityIf(x, y, WALL) != NULL)
    return ;
  newFlame = new Flame(x, y, _power, _range - 1, direction, _gameInfo);
  _gameInfo.map.addEntity(newFlame);
  if ((character = _gameInfo.map.getEntityIf(x, y, CHARACTER)) != NULL)
    (_gameInfo.map.getEntityIf(x, y, CHARACTER))->takeDamages(newFlame->_power);
  if ((object = _gameInfo.map.getEntityIfNot(x, y, CHARACTER)) != NULL)
    (_gameInfo.map.getEntityIfNot(x, y, CHARACTER))->takeDamages(newFlame->_power);
}

void	Flame::hurtCharacter(ACharacter *character, int power)
{
  character->takeDamages(power);
}
