#include "Player.hpp"

Player::Player(int x, int y, Camera *camera, glm::vec4 color, IObject *model)
  : ACharacter(x, y, color, model), _camera(camera)
{
  _camera->translate(glm::vec3(x, 0.0, y));
  _camera->setPointView(glm::vec3(x, 0.0, y));
}

Player::~Player()
{
}

bool	Player::update(gdl::Clock const &clock, Input const &input, Map &map)
{
  eAction	tab[4] = {FORWARD, BACK, LEFT, RIGHT};
  glm::vec3	dir[4] = {glm::vec3(0.0, 0.0, 1.0), glm::vec3(0.0, 0.0, -1.0),
			  glm::vec3(1.0, 0.0, 0.0), glm::vec3(-1.0, 0.0, 0.0)};
  bool		ret = false;

  for (int i = 0; i < 4; ++i)
    {
      if (input[tab[i]])
	{
	  if ((ret = updatePosition(map, tab[i])) == true)
	    {
	      _camera->translate(dir[i]);
	      return (true);
	    }
	}
    }
  return (ret);
}
