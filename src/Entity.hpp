#ifndef _ENTITY_H_
# define _ENTITY_H_

# include "AEntity.hpp"

class Entity : public AEntity
{
public:
  Entity(int x, int y, eType type, IObject *model);
  virtual ~Entity();

  void	destroy(Map &map);
  virtual bool	update(gdl::Clock const &clock, Input const &input, Map &map);
};

#endif /* _ENTITY_H_ */
