#include "GameEngine.hpp"
#include "Player.hpp"

Player::Player(int x, int y, Camera *camera, glm::vec4 color, IObject *model,
	       t_gameinfo &gameInfo)
  : ACharacter(x, y, color, model, gameInfo), _camera(camera)
{
  _camera->translate(glm::vec3(x, 0.0, y));
  _camera->setPointView(glm::vec3(x, 0.0, y));
}

Player::~Player()
{
  std::cout << "Player death" << std::endl;
}

void	Player::update(t_gameinfo &gameInfo)
{
  eAction	tab[4] = {FORWARD, BACK, LEFT, RIGHT};
  glm::vec3	dir[4] = {glm::vec3(0.0, 0.0, 1.0), glm::vec3(0.0, 0.0, -1.0),
			  glm::vec3(1.0, 0.0, 0.0), glm::vec3(-1.0, 0.0, 0.0)};
  std::cout << "Player update" << std::endl;
  for (int i = 0; i < 4; ++i)
    {
      if (gameInfo.input[tab[i]])
	{
	  if (updatePosition(gameInfo.map, tab[i]) == true)
	    {
	      _camera->translate(dir[i]);
	      break ;
	    }
	}
    }
}
