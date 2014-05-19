#ifndef _MAP_HPP_
# define _MAP_HPP_

# include <string>
# include <vector>
# include "Container.hpp"
# include "AEntity.hpp"
# include "Entity.hpp"
# include "Player.hpp"
# include "Settings.hpp"

# define MAXSIZE 10000
# define SQUARESIZE 10
# define RAD(x) ((x) * 3.14159265359 / 180)

typedef std::vector<Container *>::const_iterator v_Contcit;

typedef struct	s_spawn
{
  double       	centerX;
  double       	centerY;
  double       	radiusX;
  double       	radiusY;
  double       	angle;
  double       	angleStep;
  int		totalPlayer;
  int		toPlace;
  int		packSize;
}		t_spawn;

class Map
{
public:
  Map(Settings &set);
  ~Map();

  void	createMap(std::map<eType, IObject *> &type);
  eType	checkMapColision(int x, int y) const;

  bool		save(const std::string&);
  bool		load(Settings &settings, const std::string&,
		     std::map<eType, IObject *> &type);

  void	addEntity(AEntity *ent);
  void	removeEntity(int x, int y);
  void	removeEntityByPtr(AEntity *ptr);

  void		setEntity(int, int, eType);
  void		setEntityIf(int, int, eType, eType);
  void		setEntityIfNot(int, int, eType, eType);
  AEntity	*getEntity(int, int) const;
  AEntity	*getEntityIf(int, int, eType) const;
  AEntity	*getEntityIfNot(int, int, eType) const;

  void	spawnEnt(int nbPlayer, int nbIa, std::map<eType, IObject *> &type);

  unsigned int	getWidth() const;
  unsigned int	getHeight() const;
  unsigned int	getContPos(int x, int y) const;
  v_Contcit	ContBegin() const;
  v_Contcit	ContEnd() const;

private:
  void	genSmallMaze(short x, short y, short dir);
  void	genBigMaze();

  bool	checkValidPath(int x, int y) const;
  short	getDir(bool *tab, short oldDir) const;

  bool	checkAccess(short x, short y) const;
  void	fillBox();
  void	fillContainers(std::map<eType, IObject *> &type);
  void	display();

  void	*createCharacter(int &nbPlayer, int &nbIa);
  bool	putPlayer(int x, int y, std::map<eType, IObject *> &type);
  void	setStart(t_spawn &spawn, int pack) const;
  void	initSpawn(t_spawn &spawn, int nbPlayer, int nbIa) const;
  // void	createCharacter(int &nbPlayer, int &nbIa, int x, int y);
  unsigned short	_mapX;
  unsigned short	_mapY;
  unsigned short	_density;
  unsigned short	_linear;
  std::vector<eType>	_map;
  std::vector<Container *>	_cont;
};

#endif /* !_MAP_HPP_ */
