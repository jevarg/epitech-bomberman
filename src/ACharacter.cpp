#include "ACharacter.hpp"

ACharacter::ACharacter(glm::vec4 color, Model model)
  : AEntity(0, 0, CHARACTER), _mutex(), _condvar(), _color(color),
    _model(model), _health(1), _isAlive(true), _bombStock(1),
    _bombType(NORMAL), _speed(5), _range(5), _score(0)
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

void	ACharacter::hit()
{
  --_health;
  if (_health == 0)
    _isAlive = false;
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

int	ACharacter::getScore() const
{
  return (_score);
}

bool	ACharacter::isAlive() const
{
  return (_isAlive);
}
