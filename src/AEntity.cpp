#include "AEntity.hpp"

AEntity::AEntity()
{
}

AEntity::AEntity(int x, int y, eType type) : _x(x), _y(y), _type(type)
{
}

AEntity::~AEntity()
{
}

int	AEntity::getXPos() const
{
  return (_x);
}

int	AEntity::getYPos() const
{
  return (_y);
}

eType	AEntity::getType() const
{
  return (_type);
}

void	AEntity::setXPos(const int &x)
{
  _x = x;
}

void	AEntity::setYPos(const int &y)
{
  _y = y;
}

void	AEntity::setType(const eType &type)
{
  _type = type;
}
