#ifndef _ENTITYFACTORY_H_
# define _ENTITYFACTORY_H_

# include <map>
# include "AEntity.hpp"

class EntityFactory
{
public:
  static	EntityFactory *getInstance();

  void		addEntity(eType type, AEntity *item);
  AEntity	*getEntity(eType type, int x, int y);

private:
  EntityFactory();
  virtual ~EntityFactory();

  std::map<eType, AEntity *>	_items;
  static EntityFactory		_facto;
};

#endif /* _ITEMFACTORY_H_ */
