#ifndef _CONTAINER_H_
# define _CONTAINER_H_

# include <iostream>
# include <vector>
# include <list>
# include "AEntity.hpp"
# include "Mutex.hpp"
# include "Scopelock.hpp"

class Container;

typedef std::vector<AEntity *>::const_iterator v_Entcit;
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
  l_Entcit	listBegin() const;
  l_Entcit	listEnd() const;
  l_Entit	listBeginMod();
  l_Entit	listEndMod();
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
