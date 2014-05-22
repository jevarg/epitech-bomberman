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
  void	update(); // a virer apres le merge qui change la classe mere de Box
};

#endif /* _BOX_HPP_ */
