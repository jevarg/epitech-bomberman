#ifndef _CONTAINER_H_
# define _CONTAINER_H_

# include <iostream>
# include <vector>
# include <list>
# include "AEntitie.hpp"

class Container;

typedef std::vector<t_entity *>::const_iterator v_Entcit;
typedef std::list<t_entity *>::const_iterator l_Entcit;
typedef std::list<t_entity *>::iterator l_Entit;

class Container
{
public:
  Container();
  ~Container();

  eType	checkContColision(int x, int y) const;
  void	stockEntitie(t_entity *);
  void	removeContBlock(int x, int y);

  v_Entcit	vecBegin() const;
  v_Entcit	vecEnd() const;
  l_Entcit	listBegin() const;
  l_Entcit	listEnd() const;
  void		setMobilEnt(int, int, eType);

private:
  std::vector<t_entity *>	_staticEnt;
  std::list<t_entity *>		_mobileEnt;
};

#endif /* _ENTITIE_H_ */
