#include "GameEngine.hpp"
#include "Flame.hpp"

Flame::Flame(int x, int y, int power, int range, eDir direction, t_gameinfo &gameInfo)
  : ALivingEntity(x, y, FLAME, gameInfo)
{
  _power = power;
  _range = range;
  _direction = direction;
  _timeout = _gameInfo.set.getVar(FIRETIME)
    * (_gameInfo.set.getVar(FPS) / 1000.0);
  _nextFlame = _gameInfo.set.getVar(FIRESPEED)
    * (_gameInfo.set.getVar(FPS) / 1000.0); // first nb = delay in ms
  if (_nextFlame <= 0)
    _nextFlame = 1;
}

Flame::~Flame()
{
}

void		Flame::update()
{
  AEntity	*ent;
  bool		hit = false;

  if (_gameInfo.map.getEntityIf(_x, _y, WALL) != NULL ||
      (--_timeout) == 0)
    {
      die();
      return ;
    }
  for (int i = BOX; i < UNKNOWNENTITY; ++i)
    {
      if (i == FLAME)
	continue ;
      if ((ent = _gameInfo.map.getEntityIf(_x, _y, static_cast<eType>(i))) != NULL)
	{
	  ent->takeDamages(_power);
	  die();
	  hit = true;
	}
      if (hit)
	return ;
    }
  if ((--_nextFlame) == 0 && _range > 0)
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
  if (_gameInfo.map.getEntityIf(x, y, FLAME) == NULL)
    _gameInfo.map.addEntity(new Flame(x, y, _power, _range - 1,
				      direction, _gameInfo));
}

void	Flame::hurtCharacter(ACharacter *character, int power)
{
  character->takeDamages(power);
}
