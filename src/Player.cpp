#include "Player.hpp"

Player::Player(int x, int y, Camera *camera, glm::vec4 color, IObject *model)
  : ACharacter(x, y, color, model), _camera(camera)
{
  _camera->translate(glm::vec3(x, 0.0, y));
  _camera->setPointView(glm::vec3(x + 0.5, 0.0, y));
}

Player::~Player()
{
}

void	Player::update(gdl::Clock const &clock, Input const &input, Map &map)
{
  if (input[FORWARD] && move(FORWARD, map))
    _camera->translate(glm::vec3(0.0, 0.0, 1.0));
  if (input[BACK] && move(BACK, map))
    _camera->translate(glm::vec3(0.0, 0.0, -1.0));
  if (input[RIGHT] && move(RIGHT, map))
    _camera->translate(glm::vec3(-1.0, 0.0, 0.0));
  if (input[LEFT] && move(LEFT, map))
    _camera->translate(glm::vec3(1.0, 0.0, 0.0));
}
