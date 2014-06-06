#include "ABomb.hpp"
#include "Exception.hpp"
#include "GameEngine.hpp"
#include "Flame.hpp"

ABomb::ABomb(int x, int y, ACharacter *character, t_gameinfo *gameInfo)
  : ALivingEntity(x, y, BOMB, gameInfo)
{
  _character = character;
  _timeout = 1 * gameInfo->set->getVar(FPS);
  _gameInfo->sound->playSound("fuse");
}

ABomb::~ABomb()
{
}

void	ABomb::explode()
{
  if (die() == false)		// Already ind ead state
    return ;			// importent to die first so no colision with flame
  if (_character != NULL)
    _character->setBombStock(_character->getBombStock() + 1);
  _gameInfo->sound->playSound("explosion");
  _gameInfo->map->addEntity(new Flame(_x, _y, _power, _range, ALLDIR, _gameInfo));
}

/*
** Now wait for the bomb to esplode before deleting the player.
*/

void	ABomb::update()
{
  if ((--_timeout) == 0)
    this->explode();
}

void	ABomb::takeDamages(int /*amount*/)
{
  if (_isAlive == false)
    return ;
  explode();
}
