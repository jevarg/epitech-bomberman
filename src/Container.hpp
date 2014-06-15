#ifndef _CONTAINER_H_
# define _CONTAINER_H_

# include <iostream>
# include <vector>
# include <list>
<<<<<<< HEAD
# include "AEntity.hpp"
# include "Mutex.hpp"
# include "Scopelock.hpp"

# define IFCHARACTER(type, val) ((val == CHARACTER) ? (type == CHARACTER1 || type == CHARACTER2 || type == BOT) : (type == val))

# define IFNOTCHARACTER(type, val) ((val == CHARACTER) ? (type != CHARACTER1 && type != CHARACTER2 && type != BOT) : (type != val))


class Container;

typedef std::vector<AEntity *>::const_iterator v_Entcit;
typedef std::vector<AEntity *>::iterator v_Entit;
typedef std::list<AEntity *>::const_iterator l_Entcit;
typedef std::list<AEntity *>::iterator l_Entit;
=======
# include "AEntitie.hpp"

class Container;

typedef std::vector<t_entity *>::const_iterator v_Entcit;
typedef std::list<t_entity *>::const_iterator l_Entcit;
typedef std::list<t_entity *>::iterator l_Entit;
>>>>>>> 35c0cf39dea90a7423e4e792261ed64446d55473

class Container
{
public:
  Container();
  ~Container();

<<<<<<< HEAD
  eType	checkColision(int x, int y) const;
  void	stockEntity(AEntity *);
  void	removeContBlock(int x, int y);
  void	removeContBlockByPtr(AEntity *ptr);

  v_Entcit	vecBegin() const;
  v_Entcit	vecEnd() const;
  v_Entit	vecBeginMod();
  v_Entit	vecEndMod();
  AEntity	*vecFront() const;
  bool		vecEmpty() const;
  l_Entcit	listBegin() const;
  l_Entcit	listEnd() const;
  l_Entit	listBeginMod();
  l_Entit	listEndMod();
  AEntity	*listFront() const;
  bool		listEmpty() const;
  AEntity	*getEntity(int, int);
  AEntity	*getEntityIf(int, int, eType);
  AEntity	*getEntityIfNot(int, int, eType);

  Mutex		*getMutex() const;
private:
  std::vector<AEntity *>       	_staticEnt;
  std::list<AEntity *>     	_mobileEnt;
  Mutex				*_mutex;
=======
  eType	checkContColision(int x, int y) const;
  void	stockEntitie(t_entity *);
  void	removeContBlock(int x, int y);

  v_Entcit	vecBegin() const;
  v_Entcit	vecEnd() const;
  l_Entcit	listBegin() const;
  l_Entcit	listEnd() const;

private:
  std::vector<t_entity *>	_staticEnt;
  std::list<t_entity *>		_mobileEnt;
>>>>>>> 35c0cf39dea90a7423e4e792261ed64446d55473
};

#endif /* _ENTITIE_H_ */
