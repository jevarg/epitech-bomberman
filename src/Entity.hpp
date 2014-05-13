#ifndef _ENTITY_H_
# define _ENTITY_H_

# include "AEntity.hpp"

class Entity : public AEntity
{
public:
  Entity(int x, int y, eType type);
  virtual ~Entity();
};

#endif /* _ENTITY_H_ */
