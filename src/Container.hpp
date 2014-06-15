#ifndef _CONTAINER_H_
# define _CONTAINER_H_

# include <iostream>
# include <vector>
# include <list>
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

class Container
{
public:
  Container();
  ~Container();

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
};

#endif /* _ENTITIE_H_ */
