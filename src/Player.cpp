#include "Player.hpp"

Player::Player(int x, int y, Camera camera, glm::vec4 color, IObject *model)
  : ACharacter(x, y, color, model), _camera(camera)
{
}

Player::~Player()
{
}

void	Player::update(gdl::Clock const &, Input &)
{
}
