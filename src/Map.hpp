<<<<<<< HEAD
#ifndef _MAP_HPP_
# define _MAP_HPP_

# include <string>
# include <vector>
# include <deque>
# include "Container.hpp"
# include "AEntity.hpp"
# include "Entity.hpp"
# include "Player.hpp"
# include "Settings.hpp"
# include "ModelFactory.hpp"

# define MAXSIZE 10000
# define SQUARESIZE 8
# define RAD(x) ((x) * 3.14159265359 / 180)

typedef std::vector<Container *>::const_iterator v_Contcit;
typedef std::deque<AEntity *>::iterator	d_Ait;
=======
#ifndef _MAP_H_
# define _MAP_H_

# include <vector>
# include "Container.hpp"
# include "AEntitie.hpp"
# include "Settings.hpp"

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
>>>>>>> 35c0cf39dea90a7423e4e792261ed64446d55473

class Map
{
public:
  Map(Settings &set);
  ~Map();

<<<<<<< HEAD
  void	createMap(t_gameinfo &gameInfo);
  eType	checkMapColision(int x, int y) const;
  bool	checkFullMapColision(int x, int y, std::vector<AEntity *> &vec) const;

  void		save(const std::string&);
  void		load(const std::string &,
		     t_gameinfo &gameInfo);

  void		addEntity(AEntity * const ent);
  void		removeEntity(int x, int y);
  void		removeEntityByPtr(AEntity *ptr);
  void		pushToCollector(AEntity *ent);
  int		clearElements();


  AEntity	*getEntity(int, int) const;
  AEntity	*getEntityIf(int, int, eType) const;
  AEntity	*getEntityIfNot(int, int, eType) const;
  bool		hasPlayer() const;
  int		nbPlayer() const;

  void		setMobilEnt(int x, int y, eType type);

  unsigned int	getWidth() const;
  unsigned int	getHeight() const;
  unsigned int	getContPos(int x, int y) const;
  v_Contcit	ContBegin() const;
  v_Contcit	ContEnd() const;
  void		determineMapSize(const std::string &, int &, int &);

  void		createContainers();
  void		display();
  const std::vector<Container *>	&getCont() const;
=======
  unsigned int	getWidth() const;
  unsigned int	getHeight() const;
  void	createMap();
  void	addEntitie(t_entity *ent);
  void	removeEntity(int x, int y);
  eType	checkMapColision(int x, int y) const;

  v_Contcit	ContBegin() const;
  v_Contcit	ContEnd() const;
>>>>>>> 35c0cf39dea90a7423e4e792261ed64446d55473

private:
  void	genSmallMaze(short x, short y, short dir);
  void	genBigMaze();

  bool	checkValidPath(int x, int y) const;
  short	getDir(bool *tab, short oldDir) const;

  bool	checkAccess(short x, short y) const;
<<<<<<< HEAD
  void	fillBox();
  void	fillContainers(t_gameinfo &gameInfo);

  int			_mapX;
  int			_mapY;
=======
  unsigned int	getContPos(int x, int y) const;
  void	fillBox();
  void	fillContainers();
  void	display();

  unsigned short	_mapX;
  unsigned short	_mapY;
>>>>>>> 35c0cf39dea90a7423e4e792261ed64446d55473
  unsigned short	_density;
  unsigned short	_linear;
  std::vector<eType>	_map;
  std::vector<Container *>	_cont;
<<<<<<< HEAD
  std::deque<AEntity *>		_collector;
};

#endif /* !_MAP_HPP_ */
=======
};

#endif /* _MAP_H_ */
>>>>>>> 35c0cf39dea90a7423e4e792261ed64446d55473
