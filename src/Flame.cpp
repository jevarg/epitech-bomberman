#include "Flame.hpp"

Flame::Flame()
  : AEntitie(0, 0, FLAME), _mutex(), _condvar()
{ 
}

Flame::~Flame()
{
}

void	Flame::hurtCharacter(ACharacter *character)
{
  character->hit();
}
