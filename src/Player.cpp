#include "GameEngine.hpp"
#include "Player.hpp"

Player::Player(int x, int y, Camera *camera, glm::vec4 color,
	       t_gameinfo &gameInfo, int id)
  : ACharacter(x, y, color, gameInfo), _camera(camera)
{
  _camera->translate(glm::vec3(x, 0.0, y));
  _camera->setPointView(glm::vec3(x, 0.0, y));
  _id = id;
}

Player::~Player()
{
}

/*
** The single version checks using the action
** That means binds can be used;
*/

bool	Player::checkInputSingle()
{
  eAction	tab[4] = {FORWARD, BACK, RIGHT, LEFT};
  glm::vec3	dir[4] = {glm::vec3(0.0, 0.0, -1.0), glm::vec3(0.0, 0.0, 1.0),
			  glm::vec3(1.0, 0.0, 0.0), glm::vec3(-1.0, 0.0, 0.0)};
  bool		ret = false;

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

/*
** The multi version checks using the keyCodes
** That means binds can NOT be used
*/

bool	Player::checkInputMulti()
{
  eAction	tab[4] = {FORWARD, BACK, RIGHT, LEFT};
  SDL_Keycode	keyTab[10] = {'z', 's', 'd', 'q', SDLK_SPACE,
			     SDLK_UP, SDLK_DOWN, SDLK_RIGHT, SDLK_LEFT, SDLK_KP_ENTER};
  glm::vec3	dir[4] = {glm::vec3(0.0, 0.0, -1.0), glm::vec3(0.0, 0.0, 1.0),
			  glm::vec3(1.0, 0.0, 0.0), glm::vec3(-1.0, 0.0, 0.0)};
  int		pos = (_id == 2);
  bool		ret = false;
  int		idx;

  for (int i = pos * 5; i < 4 + pos * 5; ++i)
    {
      if (_gameInfo.input[keyTab[i]])
	{
	  idx = i > 4 ? i - 5 : i;
	  if (updatePosition(_gameInfo.map, tab[idx], _gameInfo.clock) == true)
	    {
	      _camera->translate(dir[idx] * static_cast<float>(_speed * _gameInfo.clock.getElapsed()));
	      ret = true;
	      break ;
	    }
	}
    }
  if (_gameInfo.input[keyTab[pos * 5 + 4]])
    dropBomb();
  return (ret);
}

bool	Player::checkInput()
{
  bool		ret = false;

  if (_id == 0)
    ret = checkInputSingle();
  else
    ret = checkInputMulti();
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
