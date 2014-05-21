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

class Map
{
public:
  Map(Settings &set);
  ~Map();

  void	createMap(std::map<eType, IObject *> &type, t_gameinfo gameInfo);
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

  void	setMobilEnt(int x, int y, eType type);

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
  void	fillContainers(std::map<eType, IObject *> &type, t_gameinfo &gameInfo);
  void	display();

  int			_mapX;
  int			_mapY;
  unsigned short	_density;
  unsigned short	_linear;
  std::vector<eType>	_map;
  std::vector<Container *>	_cont;
};

#endif /* !_MAP_HPP_ */
