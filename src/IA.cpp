#include <cmath>
#include "GameEngine.hpp"
#include "IA.hpp"

IA::IA(int x, int y, t_gameinfo *gameInfo, bool thread)
  : ACharacter(x, y, BOT, gameInfo, thread), _lua()
{
  _level = 2;
}

IA::~IA()
{
}

void	IA::update()
{
  int cnt = 0;
  static double aggro[] = {4.0, 8.0, 12.0, 10.0};
  double y = _y - aggro[_level - 1];
  double x = _x - aggro[_level - 1];

  pushEntitie(std::floor(x), std::floor(y), &cnt, aggro[_level - 1]);
  if (cnt != 0)
    {
      int res = getResultScript(aggro[_level - 1], static_cast<int>(_orient));
      if (res == DROPBOMB)
  	dropBomb();
      else
  	updatePosition(_gameInfo->map, static_cast<eAction>(res), _gameInfo->clock);
    }
  std::cout << "SORTI DU LUA" << std::endl;
}

void	IA::pushEntitie(int x, int y, int *cnt, int aggro)
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
	    _lua.pushCreateTable(((aggro * 2) * (aggro * 2) * 3) + 9);
	  if (i == std::floor(_y) && j == std::floor(_x))
	    {
	      if (type == BOMB)
	      	_lua.pushStringInt("bomb", 1);
	      else if (_gameInfo->map->getEntityIf(j, i, BOMB) != NULL)
	      	_lua.pushStringInt("bomb", 1);
	      else
	      	_lua.pushStringInt("bomb", 0);
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

int	IA::getResultScript(int aggro, int orient)
{
  _lua.pushStringInt("orientation", orient);
  _lua.pushStringInt("bomb_range", 4);
  _lua.pushStringInt("level", _level);
  _lua.pushStringInt("aggro", aggro);
  _lua.pushSetGlobal("arg");
  _lua.executeLua("ai/main.lua");
  return (_lua.getDatas());
}

AEntity *IA::clone(int x, int y)
{
  return (new IA(x, y, _gameInfo));
}
