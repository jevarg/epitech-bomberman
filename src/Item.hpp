#ifndef ITEM_HPP_
# define ITEM_HPP_

<<<<<<< HEAD
# include "AItem.hpp"

class	Item : public AItem
{
public:
  Item(int x, int y, t_gameinfo *gameInfo, bool thread = true);
  ~Item();

  void	setAttr(ACharacter *ch) const;
  AItem	*clone(int x, int y);
=======
# include "AEntitie.hpp"

enum	eItemType
  {
    SPEED,
    RANGE,
    ARMOR,
    STOCK
  };

class		Item : public AEntitie
{
private:
  eItemType	_itemType;

public:
  Item(eItemType itemType);
  ~Item();
  eItemType	getType() const;
>>>>>>> 35c0cf39dea90a7423e4e792261ed64446d55473
};

#endif /* !ITEM_HPP_ */
