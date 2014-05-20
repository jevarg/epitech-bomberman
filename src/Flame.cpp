#include "Flame.hpp"

Flame::Flame(int x, int y, IObject *model)
  : AEntity(x, y, FLAME, model), _mutex(), _condvar()
{
}

Flame::~Flame()
{
}

void	Flame::hurtCharacter(ACharacter *character)
{
  character->takeDamages(0);
}

bool	Flame::update(gdl::Clock const &clock, Input const &input, Map &map)
{

}
