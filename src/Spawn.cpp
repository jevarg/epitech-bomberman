#include "IA.hpp"
#include "GameEngine.hpp"
#include "Spawn.hpp"

Spawn::Spawn(Map &map) : _map(map)
{
  _mapX = map.getWidth();
  _mapY = _map.getHeight();
}

Spawn::~Spawn()
{
}

/*
** Placement of players & IA
*/

void	Spawn::spawnCharacter(t_spawn &spawn, int x, int y)
{
  int	playerId;

  if (spawn.nbPlayer > spawn.nbIa)
    {
      playerId = (!spawn.engine.gameInfo.map.hasPlayer() && spawn.nbPlayer == 1) ?
	0 : spawn.nbPlayer;
      _map.addEntity(new Player(x, y, spawn.engine.cam[0], glm::vec4(0.0),
				spawn.engine.gameInfo, playerId));
      --spawn.nbPlayer;
    }
  else
    {
      _map.addEntity(new IA(x, y, glm::vec4(0.0),
			    spawn.engine.gameInfo));
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
	  (stype = _map.checkMapColision(tx, ty)) != FREE) && radius < maxside)
    {
      tx = x - (radius + 1);
      ty = y + (radius + 1);
      dirX = 1;
      dirY = 0;
      do
	{
	  if (!(tx <= 0 || tx >= _mapX - 1 || ty <= 0 || ty >= _mapX - 1))
	    {
	      if (_map.checkMapColision(tx, ty) == FREE)
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
    {
      std::cerr << "No place for player" << std::endl;
      return (false);
    }
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
    spawn.angle = 0;
  spawn.angleStep = 360 / pack;
}

void	Spawn::initSpawn(t_spawn &spawn, int nbPlayer, int nbIa) const
{
  int	minside;

  minside = ((_mapX < _mapY) ? _mapX : _mapY) - 2;
  spawn.totalPlayer = nbPlayer + nbIa;
  spawn.toPlace = spawn.totalPlayer;
  spawn.packSize = minside / 2;
  spawn.angle = 0;
  spawn.angleStep = spawn.totalPlayer / spawn.packSize;
  spawn.centerX = _mapX / 2;
  spawn.centerY = _mapY / 2;
  spawn.toPlace = spawn.totalPlayer;
  spawn.nbPlayer = nbPlayer;
  spawn.nbIa = nbIa;
}

void	Spawn::spawnEnt(int nbPlayer, int nbIa, Camera **cam, t_gameInfo &gameInfo)
{
  t_engine	engine(cam, gameInfo);
  t_spawn	spawn(engine);
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
