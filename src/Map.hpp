#ifndef _MAP_H_
# define _MAP_H_

# include <vector>
# include "Container.hpp"
# include "AEntitie.hpp"

# define MAXSIZE 10000
# define SQUARESIZE 10

enum	e_dir
  {
    NORTH = 0,
    EAST = 1,
    SOUTH = 2,
    WEST = 3
  };

typedef std::vector<Container *>::const_iterator v_Contcit;

class Map
{
public:
  Map();
  ~Map();

  int	getWidth() const;
  int	getHeight() const;
  void	createMap();
  void	addEntitie(t_entity *ent);
  void	removeEntity(int x, int y);
  eType	checkMapColision(int x, int y) const;
  void	setMobilEnt(int x, int y, eType type);
  v_Contcit	ContBegin() const;
  v_Contcit	ContEnd() const;

private:
  void	genSmallMaze(short x, short y, short dir);
  void	genBigMaze();

  bool	checkValidPath(int x, int y) const;
  short	getDir(bool *tab, short oldDir) const;

  bool	checkAccess(short x, short y) const;
  unsigned int	getContPos(int x, int y) const;
  void	fillBox();
  void	fillContainers();
  void	display();

  unsigned short	_mapX;
  unsigned short	_mapY;
  unsigned short	_density;
  unsigned short	_linear;
  std::vector<eType>	_map;
  std::vector<Container *>	_cont;
};

#endif /* _MAP_H_ */
