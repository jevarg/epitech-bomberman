#include <iostream>
#include "ACharacter.hpp"

ACharacter::ACharacter()
{
}

ACharacter::~ACharacter()
{
}

void	ACharacter::moveForward()
{

}

void	ACharacter::moveBackward()
{

}

void	ACharacter::moveLeft()
{

}

void	ACharacter::moveRight()
{

}

bool	ACharacter::initialize()
{
  return (true);
}

void	ACharacter::update(gdl::Clock const &, gdl::Input &)
{

}

void	ACharacter::draw(gdl::AShader &shader, gdl::Clock const &clock)
{
  (void) shader;
  (void) clock;
}

int	ACharacter::getScore()
{
  return (0);
}
