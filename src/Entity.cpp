#include "Entity.hpp"

Entity::Entity(int x, int y, eType type, IObject *model) : AEntity(x, y, type, model)
{
}

Entity::~Entity()
{
}
