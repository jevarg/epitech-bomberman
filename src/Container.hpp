#ifndef _CONTAINER_H_
# define _CONTAINER_H_

# include <iostream>
# include <vector>
# include <list>
# include "AEntity.hpp"

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

  v_Entcit	vecBegin() const;
  v_Entcit	vecEnd() const;
  l_Entcit	listBegin() const;
  l_Entcit	listEnd() const;
  void		setMobilEnt(int, int, eType);

private:
  std::vector<AEntity *>	_staticEnt;
  std::list<AEntity *>		_mobileEnt;
};

#endif /* _ENTITIE_H_ */