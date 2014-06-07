#ifndef ITEM_HPP_
# define ITEM_HPP_

# include "AItem.hpp"

class	Item : public AItem
{
public:
  Item(int x, int y, t_gameinfo *gameInfo, bool thread = true);
  ~Item();

  void	setAttr(ACharacter *ch) const;
  AItem	*clone(int x, int y);
};

#endif /* !ITEM_HPP_ */
