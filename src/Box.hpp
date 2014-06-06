#ifndef _BOX_HPP_
# define _BOX_HPP_

# include "ItemFactory.hpp"
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
  Box(int x, int y, eType type, t_gameinfo *gameInfo);
  ~Box();

  void	takeDamages(int amount);
  void	spawnItem();

private:
  int	getpSize(const int *tab, int size) const;
  int	getMaxProb(const int *tab, int size) const;
  bool	sameProb(int *tab, int size) const;
  ItemFactory	*_facto;
};

#endif /* _BOX_HPP_ */
