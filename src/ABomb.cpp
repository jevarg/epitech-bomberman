#include "ABomb.hpp"
#include "Exception.hpp"
#include "GameEngine.hpp"
#include "Flame.hpp"

ABomb::ABomb(int x, int y, ACharacter *character, t_gameinfo &gameInfo)
  : ALivingEntity(x, y, BOMB, gameInfo)
{
  _character = character;
  _timeout = 1 * gameInfo.set.getVar(FPS);
}

ABomb::~ABomb()
{
}

void	ABomb::explode()
{
  die(); // importent to die first so no colision with flame
  if (_character != NULL)
    _character->setBombStock(_character->getBombStock() + 1);
  _gameInfo.map.addEntity(new Flame(_x, _y, _power, _range, ALLDIR, _gameInfo));
}

void	ABomb::update()
{
  if (_character && _character->isAlive() == false)
    _character = NULL;
  if ((--_timeout) == 0)
    this->explode();
}

void	ABomb::takeDamages(int /*amount*/)
{
  if (_isAlive == false)
    return ;
  explode();
}
