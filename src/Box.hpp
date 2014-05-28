#ifndef _BOX_HPP_
# define _BOX_HPP_

# include "ItemFactory.hpp"
# include "AEntity.hpp"
# include "SpeedItem.hpp"
# include "HealthItem.hpp"

class	Box : public AEntity
{
public:
  Box(int x, int y, eType type, t_gameinfo &gameInfo);
  ~Box();

  void	takeDamages(int amount);
  void	spawnItem(t_gameinfo &gameInfo);

private:
  ItemFactory	*_facto;
};

#endif /* _BOX_HPP_ */
