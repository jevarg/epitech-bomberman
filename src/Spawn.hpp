#ifndef _SPAWNER_H_
# define _SPAWNER_H_

# include "Map.hpp"
# include "Player.hpp"
# include "Condvar.hpp"
# include "Mutex.hpp"

typedef struct s_gameinfo	t_gameInfo;

typedef struct			s_engine
{
  s_engine(Camera **pcam, t_gameinfo &pgameInfo) :
    cam(pcam), gameInfo(pgameInfo)
  {
  }
  Camera			**cam;
  t_gameinfo			&gameInfo;
}				t_engine;

typedef struct	s_spawn
{
  s_spawn(t_engine &pEngine) : engine(pEngine)
  {
  }
  double       	centerX;
  double       	centerY;
  double       	radiusX;
  double       	radiusY;
  double       	angle;
  double       	angleStep;
  int		totalPlayer;
  int		toPlace;
  int		packSize;
  int		nbPlayer;
  int		nbIa;
  t_engine	&engine;
}		t_spawn;

class Spawn
{
public:
  Spawn(Map *map);
  virtual ~Spawn();

  void	spawnEnt(int nbPlayer, int nbIa, Camera **cam, t_gameinfo &gameInfo);
  void	setSpawnSize(int sx, int sy);

private:
  void	*createCharacter(int &nbPlayer, int &nbIa);
  bool	putPlayer(int x, int y, t_spawn &spawn);
  void	setStart(t_spawn &spawn, int pack) const;
  void	initSpawn(t_spawn &spawn, int nbPlayer, int nbIa) const;
  void	spawnCharacter(t_spawn &spawn, int x, int y);

  Map		*_map;
  int		_mapX;
  int		_mapY;
};

#endif /* _SPAWNER_H_ */
