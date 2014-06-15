#ifndef _BOX_HPP_
# define _BOX_HPP_

# include "EntityFactory.hpp"
# include "AEntity.hpp"
# include "SpeedItem.hpp"
# include "HealthItem.hpp"

enum
  {
    PCHICKEN = 5,
    PSPEED = 20,
    PHEALTH = 30,
    PSTOCK = 40,
    PRANGE = 30,
    PEMPTY = 20
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
  int		getpSize(const double *tab, int size) const;
  double	getMaxProb(const double *tab, int size) const;
  int		getMinProbPos(const double *tab, int size) const;
  int		hasSame(double * const tab, int size) const;
  void		selectSameProb(double * const tab, int size) const;
  void		scaleToPercent(double * const tab, int size) const;
};

#endif /* _BOX_HPP_ */
