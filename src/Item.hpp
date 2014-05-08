#ifndef ITEM_HPP_
# define ITEM_HPP_

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
  Item();
  ~Item();
  eItemType	getType() const;
};

#endif /* !ITEM_HPP_ */
