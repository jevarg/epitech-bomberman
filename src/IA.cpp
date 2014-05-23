#include "GameEngine.hpp"
#include "IA.hpp"

IA::IA(int x, int y, glm::vec4 color, t_gameinfo &gameInfo)
  : ACharacter(x, y, color, gameInfo), _lua()
{
  _level = 2;
}

IA::~IA()
{
}

void	IA::update(t_gameinfo &gameInfo)
{
  int cnt = 0;
  int aggro[] = {4, 8, 12, 10};
  int y = _y - aggro[_level - 1];
  int x = _x - aggro[_level - 1];

  if (y < 1)
    y = 1;
  if (x < 1)
    x = 1;
  pushEntitie(x, y, &cnt, aggro[_level - 1], gameInfo);
  if (cnt != 0)
    {
      int res = getResultScript(aggro[_level - 1], static_cast<int>(_orient));
      std::cout << _x << " " << _y << " " << res << std::endl;
      updatePosition(gameInfo.map, static_cast<eAction>(res));
      getchar();
    }
}

void	IA::pushEntitie(int x, int y, int *cnt, int aggro, t_gameinfo &gameInfo)
{
  int c1 = 1;
  int c2 = 1;

  for (int i = y ; i < y + (aggro * 2); ++i)
    {
      c2 = 1;
      for (int j = x ; j < x + (aggro * 2); ++j)
	{
	  if (*cnt == 0)
	    _lua.pushCreateTable(((aggro * 2) * (aggro * 2) * 4) + 8);
	  if (i == _y && j == _x)
	    {
	      _lua.pushStringInt("y", c1);
	      _lua.pushStringInt("x", c2);
	    }
	  _lua.pushIntInt(++(*cnt), gameInfo.map.checkMapColision(j, i));
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
