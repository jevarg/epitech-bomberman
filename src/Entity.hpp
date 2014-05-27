#ifndef _ENTITY_H_
# define _ENTITY_H_

# include "AEntity.hpp"
# include "GameEngine.hpp"

class Entity : public AEntity
{
public:
  Entity(int x, int y, eType type, t_gameinfo &gameInfo);
  virtual ~Entity();

  void	takeDamages(int amount);
};

#endif /* _ENTITY_H_ */
