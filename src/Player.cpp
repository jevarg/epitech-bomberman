#include "Player.hpp"

Player::Player(int x, int y, Camera camera, glm::vec4 color, IObject *model)
  : ACharacter(x, y, color, model), _camera(camera)
{
}

Player::~Player()
{
}

void	Player::update(gdl::Clock const &clock, Input const &input, Map &map)
{
  eAction	tab[4] = {FORWARD, BACK, LEFT, RIGHT};

  for (int i = 0; i < 4; ++i)
    {
      if (input[tab[i]])
	updatePosition(map, tab[i]);
    }
}
