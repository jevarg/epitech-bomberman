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

void	IA::update()
{
  int cnt = 0;
  int aggro[] = {4, 8, 12, 10};
  int y = _y - aggro[_level - 1];
  int x = _x - aggro[_level - 1];

  pushEntitie(x, y, &cnt, aggro[_level - 1], _gameInfo);
  if (cnt != 0)
    {
      int res = getResultScript(aggro[_level - 1], static_cast<int>(_orient));
      if (res == 4)
	dropBomb(_gameInfo);
      else
	updatePosition(_gameInfo.map, static_cast<eAction>(res));
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
	  int type = gameInfo.map.checkMapColision(j, i);
	  if (*cnt == 0)
	    _lua.pushCreateTable(((aggro * 2) * (aggro * 2) * 4) + 8);	
	  if (i == _y && j == _x)
	    {
	      if (type == BOMB)
		{
		  std::cout << "Mmmmh on a de la bombe par ici" << std::endl;
		  _lua.pushStringInt("bomb", 1);
		}
	      else if (gameInfo.map.getEntityIf(j, i, BOMB) != NULL)
		{
		  _lua.pushStringInt("bomb", 1);
		}
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
