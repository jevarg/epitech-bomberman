#ifndef ITEM_HPP_
# define ITEM_HPP_

# include "AItem.hpp"

class	Item : public AItem
{
public:
  Item(int x, int y, eType type, t_gameinfo &gameInfo);
  ~Item();

  void	setAttr(ACharacter *ch) const;
};

#endif /* !ITEM_HPP_ */
