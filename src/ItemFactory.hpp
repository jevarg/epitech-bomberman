#ifndef _ITEMFACTORY_H_
# define _ITEMFACTORY_H_

# include <map>
# include "AItem.hpp"

class ItemFactory
{
public:
  static	ItemFactory *getInstance();

  void	addItem(eType type, AItem *item);
  AItem	*getItem(eType type, int x, int y);

private:
  ItemFactory();
  virtual ~ItemFactory();

  std::map<eType, AItem *>	_items;
  static ItemFactory		_facto;
};

#endif /* _ITEMFACTORY_H_ */
