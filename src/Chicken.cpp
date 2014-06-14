#include <cmath>
#include "GameEngine.hpp"
#include "Chicken.hpp"

Chicken::Chicken(int x, int y, t_gameinfo *gameInfo, bool thread)
  : ACharacter(x, y, CHICKEN, gameInfo, thread), _lua()
{
  if (thread)
    gameInfo->sound->play("chickenspawn", EFFECT);
  _health = 200;
}

Chicken::~Chicken()
{
}

void	Chicken::update()
{
  int cnt = 0;
  double y = _y - 2;
  double x = _x - 2;

  pushEntitie(std::floor(x), std::floor(y), &cnt, 2);
  if (cnt != 0)
    {
      int res = getResultScript(static_cast<int>(_orient), "ai/passiveAi.lua");
      updatePosition(_gameInfo->map, static_cast<eAction>(res), _gameInfo->clock);
    }
}

void	Chicken::pushEntitie(int x, int y, int *cnt, int aggro)
{
  int c1 = 1;
  int c2 = 1;

  for (int i = y ; i < y + (aggro * 2) + 1; ++i)
    {
      c2 = 1;
      for (int j = x ; j < x + (aggro * 2) + 1; ++j)
	{
	  int type = _gameInfo->map->checkMapColision(j, i);
	  if (*cnt == 0)
	    _lua.pushCreateTable(((aggro * 2) * (aggro * 2) * 4) + 4);
	  if (i == std::floor(_y) && j == std::floor(_x))
	    {
	      _lua.pushStringInt("y", c1);
	      _lua.pushStringInt("x", c2);
	    }
	  _lua.pushIntInt(++(*cnt), type);
	  _lua.pushIntInt(++(*cnt), c1);
	  _lua.pushIntInt(++(*cnt), c2);
	  ++c2;
	}
      ++c1;
    }
}

int	Chicken::getResultScript(int orient, const char *fileName)
{
  _lua.pushStringInt("orientation", orient);
  _lua.pushStringInt("aggro", 2);
  _lua.pushSetGlobal("arg");
  _lua.executeLua(fileName);
  return (_lua.getDatas());
}

AEntity *Chicken::clone(int x, int y)
{
  return (new Chicken(x, y, _gameInfo));
}

void	Chicken::takeDamages(int)
{
  _gameInfo->sound->play("chickenhurt", EFFECT);
}
