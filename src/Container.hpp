#ifndef _CONTAINER_H_
# define _CONTAINER_H_

# include <iostream>
# include <vector>
# include <list>
# include "AEntitie.hpp"

class Container
{
public:
  Container();
  ~Container();

  bool	checkColision();
  void	stockEntitie(AEntitie *);
private:
  std::vector<AEntitie *>	_staticEnt;
  std::list<AEntitie *>		_mobileEnt;
};

#endif /* _ENTITIE_H_ */
