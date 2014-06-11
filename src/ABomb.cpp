#include "ABomb.hpp"
#include "Exception.hpp"
#include "GameEngine.hpp"
#include "Flame.hpp"

ABomb::ABomb(int x, int y, ACharacter *character, t_gameinfo *gameInfo, bool thread)
  : ALivingEntity(x, y, BOMB, gameInfo, thread)
{
  _character = character;
  _timeout = 1 * gameInfo->set->getVar(FPS);
  if (thread)
    _gameInfo->sound->play("fuse", EFFECT);
}

ABomb::~ABomb()
{
}

void	ABomb::explode()
{
  _gameInfo->map->addEntity(new Flame(_x, _y, _power, _range, ALLDIR, _gameInfo));
  if (die() == false)		// Already ind ead state
    return ;			// importent to die first so no colision with flame
  if (_character != NULL)
    _character->setBombStock(_character->getBombStock() + 1);
  _gameInfo->sound->play("explosion", EFFECT);
}

/*
** Now wait for the bomb to esplode before deleting the player.
*/

void	ABomb::update()
{
  if ((--_timeout) == 0)
    explode();
}

void	ABomb::takeDamages(int /*amount*/)
{
  if (_isAlive == false)
    return ;
  explode();
}

void	ABomb::setRange(int range)
{
  _range = range;
}

int	ABomb::getRange() const
{
  return (_range);
}
