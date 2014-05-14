#include "Map.hpp"
#include "AEntity.hpp"

AEntity::AEntity()
{
}

AEntity::AEntity(int x, int y, eType type, IObject *model) : _x(x), _y(y), _type(type), _model(model)
{
  _model->translate(glm::vec3((float)(x * 2), 0.0, (float)(y * 2)));
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

void	AEntity::draw(gdl::AShader &shader, gdl::Clock &clock)
{
  _model->draw(shader, clock);
}
