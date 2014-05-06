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

private:
  void	generateMaze(int x, int y);
  bool	checkValidPath(int x, int y) const;
  void	display();

  int	_mapX;
  int	_mapY;
  int	_density;
  std::vector<e_path> _map;
};

#endif /* _MAP_H_ */
