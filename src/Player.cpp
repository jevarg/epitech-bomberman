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
  if (input[FORWARD])
    move(FORWARD, map);
  if (input[BACK])
    move(BACK, map);
  if (input[RIGHT])
    move(RIGHT, map);
  if (input[LEFT])
    move(LEFT, map);
}
