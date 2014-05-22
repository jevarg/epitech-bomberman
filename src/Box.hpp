#ifndef _BOX_HPP_
# define _BOX_HPP_

# include "ALivingEntity.hpp"

class	Box : public ALivingEntity
{
public:
  Box(int x, int y, t_gameinfo &gameInfo);
  ~Box();
  void	update(t_gameinfo &gameInfo);
  void	die();
};

#endif /* _BOX_HPP_ */
