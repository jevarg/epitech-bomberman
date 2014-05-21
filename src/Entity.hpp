#ifndef _ENTITY_H_
# define _ENTITY_H_

# include "AEntity.hpp"
# include "GameEngine.hpp"

class Entity : public AEntity
{
public:
  Entity(int x, int y, eType type);
  virtual ~Entity();

  void	destroy(Map &map);
  virtual void	update(t_gameinfo &gameInfo);
};

#endif /* _ENTITY_H_ */
