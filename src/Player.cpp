#include "Player.hpp"

Player::Player(int x, int y, Camera camera, glm::vec4 color, IObject *model)
  : ACharacter(x, y, color, model), _camera(camera)
{
}

Player::~Player()
{
}

bool	Player::update(gdl::Clock const &clock, Input const &input, Map &map)
{
  eAction	tab[4] = {FORWARD, BACK, LEFT, RIGHT};
  bool		ret = false;

  for (int i = 0; i < 4; ++i)
    {
      if (input[tab[i]])
	{
	  if ((ret = updatePosition(map, tab[i])) == true)
	    return (true);
	}
    }
  return (ret);
}
