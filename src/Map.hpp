#ifndef _MAP_H_
# define _MAP_H_

# include <vector>
# include "AEntitie.hpp"

enum	e_path
  {
    FREE = 0,
    USED,
    BOX
  };

enum	e_dir
  {
    NORTH = 0,
    EAST = 1,
    SOUTH = 2,
    WEST = 3
  };

class Map
{
public:
  Map();
  ~Map();

  int	getWidth() const;
  int	getHeight() const;
  void	createMap();

private:
  void	genSmallMaze(short x, short y, short pos);
  bool	checkValidPath(short x, short y) const;
  bool	checkAccess(short x, short y) const;
  short	getDir(bool *tab, short oldDir) const;
  void	fillBox();
  void	display();

  short	_mapX;
  short	_mapY;
  short	_density;
  short	_linear;
  std::vector<e_path> _map;
};

#endif /* _MAP_H_ */
