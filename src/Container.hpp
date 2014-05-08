#ifndef _CONTAINER_H_
# define _CONTAINER_H_

# include <iostream>
# include <vector>
# include <list>
# include "AEntitie.hpp"

class Container;

typedef std::vector<AEntitie *>::const_iterator v_Entcit;
typedef std::list<AEntitie *>::const_iterator l_Entcit;

class Container
{
public:
  Container();
  ~Container();

  bool	checkColision();
  void	stockEntitie(AEntitie *);
  v_Entcit	vecBegin() const;
  v_Entcit	vecEnd() const;
  l_Entcit	listBegin() const;
  l_Entcit	listEnd() const;

private:
  std::vector<AEntitie *>	_staticEnt;
  std::list<AEntitie *>		_mobileEnt;
};

#endif /* _ENTITIE_H_ */
