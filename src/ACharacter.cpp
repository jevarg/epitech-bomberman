#include "ACharacter.hpp"

ACharacter::ACharacter(glm::vec4 color, Model model)
  : AEntity(0, 0, CHARACTER), _mutex(), _condvar(), _color(color),
    _model(model), _health(1), _isAlive(true), _bombStock(1),
    _bombType(NORMAL), _speed(5), _range(5), _score(0)
{
  pthread_t         thread;

  if (pthread_create(&thread, NULL, &handle_thread, this) != 0)
    throw (Exception("Can't create Acharacter's thread"));
  _thread = thread;
}

ACharacter::~ACharacter()
{
}

void	ACharacter::move()
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

void	ACharacter::update(gdl::Clock const &clock, gdl::Input &input)
{
  (void) clock;
  (void) input;
}

void	ACharacter::draw(gdl::AShader &shader, gdl::Clock const &clock)
{
  _model.draw(shader, clock);
}

int	ACharacter::getScore() const
{
  return (_score);
}

bool	ACharacter::isAlive() const
{
  return (_isAlive);
}

void	*handle_thread(void *arg)
{
  (void) arg;
  return (NULL);
}
