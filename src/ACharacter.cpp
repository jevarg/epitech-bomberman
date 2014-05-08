#include "ACharacter.hpp"

ACharacter::ACharacter(glm::vec4 color, Model model)
  : AEntitie(0, 0, CHARACTER), _color(color), _model(model), _bombStock(1),
    _score(0), _speed(5), _range(5), _bombType(NORMAL)
{
}

ACharacter::~ACharacter()
{
}

void	ACharacter::moveUp()
{

}

void	ACharacter::moveDown()
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
  return (_score);
}
