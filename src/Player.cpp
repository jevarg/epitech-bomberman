#include "GameEngine.hpp"
#include "Player.hpp"

Player::Player(int x, int y, Camera *camera, glm::vec4 color, t_gameinfo &gameInfo)
  : ACharacter(x, y, color, gameInfo), _camera(camera)
{
  _camera->translate(glm::vec3(x, 0.0, y));
  _camera->setPointView(glm::vec3(x, 0.0, y));
}

Player::~Player()
{
  std::cout << "Player death" << std::endl;
}

bool	Player::checkInput()
{
  bool		ret = false;
  eAction	tab[4] = {FORWARD, BACK, RIGHT, LEFT};
  glm::vec3	dir[4] = {glm::vec3(0.0, 0.0, -1.0), glm::vec3(0.0, 0.0, 1.0),
			  glm::vec3(1.0, 0.0, 0.0), glm::vec3(-1.0, 0.0, 0.0)};
  for (int i = 0; i < 4; ++i)
    {
      if (_gameInfo.input[tab[i]])
	{
	  if (updatePosition(_gameInfo.map, tab[i], _gameInfo.clock) == true)
	    {
	      _camera->translate(dir[i] * static_cast<float>(_speed * _gameInfo.clock.getElapsed()));
	      ret = true;
	      break ;
	    }
	}
    }
  if (_gameInfo.input[DROPBOMB])
    dropBomb();
  return (ret);
}

void	Player::update()
{
  if (checkInput() == false && _anim == RUN)
    {
      //std::cout << "dyn: " <<  dynamic_cast<Model *>(_model)->getModel()->getAnimationFrameNumber(0) << std::endl;
      dynamic_cast<Model *>(_model)->getModel()->setCurrentAnim(dynamic_cast<Model *>(_model)->getModel()->getAnimationFrameNumber(0), false);
      _anim = NOTHING;
    }
}
