#ifndef _ENTITY_H_
# define _ENTITY_H_

# include "AEntity.hpp"

typedef struct s_gameinfo	t_gameinfo;

class Entity : public AEntity
{
public:
  Entity(int x, int y, eType type, t_gameinfo *gameInfo);
  virtual ~Entity();

  void	takeDamages(int amount);
  AEntity *clone(int x, int y);
};

#endif /* _ENTITY_H_ */
