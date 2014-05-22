#ifndef _BOX_HPP_
# define _BOX_HPP_

# include "AEntity.hpp"

class	Box : public AEntity
{
public:
  Box(int x, int y, eType type, t_gameinfo &gameInfo);
  ~Box();

  void	takeDamages(int amount);
  void	destroy(Map &map);
};

#endif /* _BOX_HPP_ */
