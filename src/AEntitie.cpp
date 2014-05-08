#include "AEntitie.hpp"

AEntitie::AEntitie()
{
}

AEntitie::AEntitie(int x, int y, eType type) : _x(x), _y(y), _type(type)
{
}

AEntitie::~AEntitie()
{
}

int	AEntitie::getXPos() const
{
  return (_x);
}

int	AEntitie::getYPos() const
{
  return (_y);
}

eType	AEntitie::getType() const
{
  return (_type);
}

void	AEntitie::setXPos(const int &x)
{
  _x = x;
}

void	AEntitie::setYPos(const int &y)
{
  _y = y;
}

void	AEntitie::setType(const eType &type)
{
  _type = type;
}
