#include "Chicken.hpp"
#include "IA.hpp"
#include "GameEngine.hpp"
#include "Spawn.hpp"

Spawn::Spawn(Map *map) : _map(map)
{
  _mapX = map->getWidth();
  _mapY = map->getHeight();
}

Spawn::~Spawn()
{
}

/*
** Placement of players & IA
*/

void	Spawn::spawnCharacter(t_spawn &spawn, int x, int y)
{
  EntityFactory	*fact = EntityFactory::getInstance();

  if (spawn.nbPlayer > spawn.nbIa)
    {
      if (!spawn.gameInfo.map->hasPlayer())
	_map->addEntity(fact->getEntity(CHARACTER1, x, y));
      else
	_map->addEntity(fact->getEntity(CHARACTER2, x, y));
      --spawn.nbPlayer;
    }
  else
    {
      _map->addEntity(fact->getEntity(BOT, x, y));
      --spawn.nbIa;
    }
}

bool	Spawn::putPlayer(int x, int y, t_spawn &spawn)
{
  int	tx = x;
  int	ty = y;
  int	radius = 0;
  char	dirX;
  char	dirY;
  eType	stype = CHARACTER;
  int	maxside = (_mapX > _mapY) ? _mapX : _mapY;

  while (((tx <= 0 || tx >= _mapX - 1 || ty <= 0 || ty >= _mapX - 1) ||
	  (stype = _map->checkMapColision(tx, ty)) != FREE) && radius < maxside)
    {
      tx = x - (radius + 1);
      ty = y + (radius + 1);
      dirX = 1;
      dirY = 0;
      do
	{
	  if (!(tx <= 0 || tx >= _mapX - 1 || ty <= 0 || ty >= _mapX - 1))
	    {
	      if (_map->checkMapColision(tx, ty) == FREE)
		break ;
	    }
	  tx += dirX;
	  ty += dirY;
	  if (dirX == 1 && dirY == 0 &&
	      tx == (x + (radius + 1)) && ty == (y + (radius + 1)))
	    {
	      dirX = 0;
	      dirY = -1;
	    }
	  else if (dirX == 0 && dirY == -1 &&
		   tx == (x + (radius + 1)) && ty == (y - (radius + 1)))
	    {
	      dirX = -1;
	      dirY = 0;
	    }
	  else if (dirX == -1 && dirY == 0 &&
		   tx == (x - (radius + 1)) && ty == (y - (radius + 1)))
	    {
	      dirX = 0;
	      dirY = 1;
	    }
	}
      while (tx != (x - (radius + 1)) || ty != (y + (radius + 1)));
      ++radius;
    }
  if (stype == FREE)
    spawnCharacter(spawn, tx, ty);
  else
    throw (Exception("No place for player"));
  return (true);
}

void	Spawn::setStart(t_spawn &spawn, int pack) const
{
  double	totalSquare;
  double	cuSquare;
  double	stepX;
  double	stepY;

  totalSquare = (std::ceil((spawn.toPlace - 1.0) / spawn.packSize)
		 * spawn.packSize) / spawn.packSize;
  cuSquare = (std::ceil((spawn.totalPlayer - 1.0) / spawn.packSize)
	      * spawn.packSize) / spawn.packSize;
  stepX = (_mapX / 2.0 - 1.0) / totalSquare;
  stepY = (_mapY / 2.0 - 1.0) / totalSquare;
  spawn.radiusX = (_mapX / 2.0 - 1.0) - ((totalSquare - cuSquare) * stepX);
  spawn.radiusY =  (_mapY / 2.0 - 1.0) - ((totalSquare - cuSquare) * stepY);
  spawn.angleStep = 360 / pack;
  if ((spawn.totalPlayer / spawn.packSize) % 2 != 0)
    spawn.angle = spawn.angleStep / 2;
  else
    spawn.angle = std::rand() % 360;
  spawn.angleStep = 360 / pack;
}

void	Spawn::initSpawn(t_spawn &spawn, int nbPlayer, int nbIa) const
{
  int	minside;

  minside = ((_mapX < _mapY) ? _mapX : _mapY) - 2;
  spawn.totalPlayer = nbPlayer + nbIa;
  spawn.toPlace = spawn.totalPlayer;
  spawn.packSize = minside / 2;
  spawn.angle = std::rand() % 360;
  spawn.angleStep = spawn.totalPlayer / spawn.packSize;
  spawn.centerX = _mapX / 2;
  spawn.centerY = _mapY / 2;
  spawn.toPlace = spawn.totalPlayer;
  spawn.nbPlayer = nbPlayer;
  spawn.nbIa = nbIa;
}

void	Spawn::spawnEnt(int nbPlayer, int nbIa, t_gameInfo &gameInfo)
{
  t_spawn	spawn(gameInfo);
  int	x = 0;
  int	y = 0;
  int	pack;

  if (nbPlayer + nbIa <= 0)
    return ;
  initSpawn(spawn, nbPlayer, nbIa);
  while (spawn.totalPlayer > 0)
    {
      if (spawn.totalPlayer == 1)
	{
	  x = _mapX / 2;
	  y = _mapY / 2;
	  if (putPlayer(x, y, spawn) == false)
	    return ;
	  --spawn.totalPlayer;
	  continue ;
	}
      pack = (spawn.totalPlayer < spawn.packSize) ?
	spawn.totalPlayer : spawn.packSize;
      setStart(spawn, pack);
      for (int i = 0; i < pack; ++i)
	{
	  x = std::floor((_mapX / 2) + cos(RAD(spawn.angle))
			 * spawn.radiusX + 0.5);
	  y = std::floor((_mapY / 2) + sin(RAD(spawn.angle))
			 * spawn.radiusY + 0.5);
	  if (putPlayer(x, y, spawn) == false)
	    return ;
	  spawn.angle = (spawn.angle += spawn.angleStep) > 360 ?
	    spawn.angle - 360 : spawn.angle;
	  --spawn.totalPlayer;
	}
    }
}

void	Spawn::setSpawnSize(int sx, int sy)
{
  _mapX = sx;
  _mapY = sy;
}
