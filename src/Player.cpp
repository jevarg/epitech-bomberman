#include "Player.hpp"

Player::Player(Camera camera, glm::vec4 color, Model model)
  : ACharacter(color, model)
{
  (void) camera;
}

Player::~Player()
{
}

void	Player::update(gdl::Clock const &, gdl::Input &)
{

}
