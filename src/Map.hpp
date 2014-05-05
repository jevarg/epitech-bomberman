#ifndef _MAP_H_
# define _MAP_H_

# include <list>
# include "AEntitie.hpp"

enum	e_path
  {
    FREE = 0,
    USED
  };

enum	e_dir
  {
    NORTH = 0,
    EAST,
    SOUTH,
    WEST
  };

class Map
{
public:
  Map();
  ~Map();

  int	getWidth() const;
  int	getHeight() const;
  void	createMap();
  void	generateMaze(int x, int y);
private:
  int	_mapX;
  int	_mapY;
  std::list<e_path> _map;
};

#endif /* _MAP_H_ */
