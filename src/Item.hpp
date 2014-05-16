#ifndef ITEM_HPP_
# define ITEM_HPP_

# include "AEntity.hpp"

enum	eItemType
  {
    SPEED,
    RANGE,
    ARMOR,
    STOCK
  };

class		Item : public AEntity
{
private:
  eItemType	_itemType;

public:
  Item(eItemType itemType);
  ~Item();

  eItemType	getItemType() const;
};

#endif /* !ITEM_HPP_ */
