#include <cmath>
#include "GameEngine.hpp"
#include "IA.hpp"

IA::IA(int x, int y, t_gameinfo *gameInfo, bool thread)
  : ACharacter(x, y, BOT, gameInfo, thread), _lua()
{
  _level = 3;
}

IA::~IA()
{
}

void	IA::update()
{
  static double aggro[] = {4.0, 8.0, 12.0};
  int cnt = 0;
  double y = _y - aggro[_level - 1];
  double x = _x - aggro[_level - 1];

  pushEntitie(std::floor(x), std::floor(y), &cnt, aggro[_level - 1]);
  if (cnt != 0)
    {
      int res = getResultScript(aggro[_level - 1], static_cast<int>(_orient), "ai/main.lua");
      // std::cout << "script returned " << res << std::endl;
      if (res == DROPBOMB)
	dropBomb();
      else
	updatePosition(_gameInfo->map, static_cast<eAction>(res), _gameInfo->clock);
    }
}

void	IA::danger_in_dir(int i, int j, int x, int y,
			  int i_x, int i_y, int max_it, int *cnt)
{
  int	k = 0;
  while (k < max_it + 1)
    {
      int type = _gameInfo->map->checkMapColision(j, i);
      if (type == FREE || type == ITEM || type == SPEEDITEM ||
	  type == HEALTHITEM || type == STOCKITEM || type == RANGEITEM)
	{
	  _lua.pushIntInt(++(*cnt), FLAME);
	  _lua.pushIntInt(++(*cnt), y);
	  _lua.pushIntInt(++(*cnt), x);
	  x += i_x;
	  y += i_y;
	  j += i_x;
	  i += i_y;
	  if (type == ITEM || type == SPEEDITEM ||
	      type == HEALTHITEM || type == STOCKITEM || type == RANGEITEM)
	    return ;
	  ++k;
	}
      else
	return ;
    }
}

void	IA::put_abstract_flame(Flame *ff, int i, int j,
			       int c1, int c2, int *cnt)
{
  int dir = ff->getDirection();
  static int dir_x[4] = {0, -1, 0, 1};
  static int dir_y[4] = {-1, 0, 1, 0};

  if (dir == ALLDIR)
    {
      danger_in_dir(i + 1, j, c2, c1 + 1, 0, 1, ff->getRange(), cnt);
      danger_in_dir(i, j + 1, c2 + 1, c1, 1, 0, ff->getRange(), cnt);
      danger_in_dir(i - 1, j, c2, c1 - 1, 0, -1, ff->getRange(), cnt);
      danger_in_dir(i, j + 1, c2 - 1, c1, -1, 0, ff->getRange(), cnt);
    }
  else
    danger_in_dir(i, j, c2, c1, dir_x[dir], dir_y[dir], ff->getRange() + 1, cnt);
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
	    _lua.pushCreateTable(((aggro * 2) * (aggro * 2) * 4) + 9);
	  Flame	*ff;
	  if ((ff = static_cast<Flame*>(_gameInfo->map->getEntityIf(j, i, FLAME))) != NULL)
	    put_abstract_flame(ff, i, j, c1, c2, cnt);
	  if (i == std::floor(_y) && j == std::floor(_x))
	    {
	      if (type == BOMB || _gameInfo->map->getEntityIf(j, i, BOMB) != NULL)
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

int	IA::getResultScript(int aggro, int orient, const char *fileName)
{
  _lua.pushStringInt("orientation", orient);
  _lua.pushStringInt("bomb_range", 4);
  _lua.pushStringInt("level", _level);
  _lua.pushStringInt("aggro", aggro);
  _lua.pushSetGlobal("arg");
  _lua.executeLua(fileName);
  return (_lua.getDatas());
}

AEntity *IA::clone(int x, int y)
{
  return (new IA(x, y, _gameInfo));
}
