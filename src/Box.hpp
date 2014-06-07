#ifndef _BOX_HPP_
# define _BOX_HPP_

# include "EntityFactory.hpp"
# include "AEntity.hpp"
# include "SpeedItem.hpp"
# include "HealthItem.hpp"

enum
  {
    PSPEED = 50,
    PHEALTH = 50
  };

class	Box : public AEntity
{
public:
  Box(int x, int y, t_gameinfo *gameInfo);
  ~Box();

  void	takeDamages(int amount);
  void	spawnItem();
  AEntity *clone(int x, int y);

private:
  int	getpSize(const int *tab, int size) const;
  int	getMaxProb(const int *tab, int size) const;
  bool	sameProb(int *tab, int size) const;
};

#endif /* _BOX_HPP_ */
