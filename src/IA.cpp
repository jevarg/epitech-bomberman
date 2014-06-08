#include <cmath>
#include "GameEngine.hpp"
#include "IA.hpp"
#include "Flame.hpp"

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
}

void	IA::danger_in_dir(int x, int y, int min_x, int max_x, int min_y,
			  int max_y, int i_x, int i_y, int max_it, int *cnt)
{
  for (int i = 0 ; i < max_it ; i++)
    {
      // std::cout << "x " << x << std::endl;
      // std::cout << "y " << y << std::endl;
      // std::cout << "minx " << min_x << std::endl;
      // std::cout << "miny " << min_y << std::endl;
      // std::cout << "maxx " << max_x << std::endl;
      // std::cout << "maxy " << max_y << std::endl;
      // std::cout << "return of getentity " << _gameInfo->map->getEntityIf(x, y, FREE) << std::endl;
      // std::cout << std::endl;
      if (x > min_x && x < max_x && y > min_y && y < max_y &&
	  _gameInfo->map->getEntityIf(x, y, FREE) == NULL)
	{
	  // std::cout << "Danger in dir at " << x << " " << y << std::endl;
	  _lua.pushIntInt(++(*cnt), FLAME);
	  _lua.pushIntInt(++(*cnt), y);
	  _lua.pushIntInt(++(*cnt), x);	
	  x += i_x;
	  y += i_y;
	}
      else
	return ;
    }
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
	    {
	      // std::cout << "find flame" << std::endl;
	      int dir = ff->getDirection();
	      if (dir == ALLDIR)
	  	{
		  // std::cout << "in alldir" << std::endl;
	  	  danger_in_dir(c2, c1 - 1, x, x + (aggro * 2) + 1, y,
				y + (aggro * 2) + 1, 0, -1, ff->getRange(), cnt);
	  	  danger_in_dir(c2, c1 + 1, x, x + (aggro * 2) + 1, y,
				y + (aggro * 2) + 1, 0, 1, ff->getRange(), cnt);
	  	  danger_in_dir(c2 + 1, c1, x, x + (aggro * 2) + 1, y,
				y + (aggro * 2) + 1, 1, 0, ff->getRange(), cnt);
	  	  danger_in_dir(c2 - 1, c1, x, x + (aggro * 2) + 1, y,
				y + (aggro * 2) + 1, -1, 0, ff->getRange(), cnt);
	  	}
	      else
	  	{
	  	  static int dir_x[4] = {0, -1, 0, 1};
	  	  static int dir_y[4] = {-1, 0, 1, 0};
	  	  danger_in_dir(c2, c1, x, x + (aggro * 2) + 1, y,
				y + (aggro * 2) + 1, dir_x[dir], dir_y[dir], ff->getRange(), cnt);
	  	}
	    }
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
