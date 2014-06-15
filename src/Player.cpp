#include "GameEngine.hpp"
#include "Player.hpp"

Player::Player(int x, int y, t_gameinfo *gameInfo, eType type, bool multi, bool thread)
  : ACharacter(x, y, type, gameInfo, thread), _camera(gameInfo, multi)
{
  _camera.translate(glm::vec3(x, 5.0, 10.0));
  _camera.setPointView(glm::vec3(x, 0.0, y));
  _multi = multi;
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
  float		d;

  for (int i = 0; i < 4; ++i)
    {
      if ((*_gameInfo->input)[tab[i]])
	{
	  if (updatePosition(_gameInfo->map, tab[i], _gameInfo->clock) == true)
	    {
	      d = ((_speed * _gameInfo->clock->getElapsed()) > 1 ? 1
		   : (_speed * _gameInfo->clock->getElapsed()));
	      _camera.translate(dir[i] * d);
	      ret = true;
	    }
	}
    }
  if ((*_gameInfo->input)[DROPBOMB])
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
  int		pos = (_type == CHARACTER2);
  bool		ret = false;
  int		idx;
  float		d;

  for (int i = pos * 5; i < 4 + pos * 5; ++i)
    {
      if (_gameInfo->input->isPressed(keyTab[i]))
	{
	  idx = i > 4 ? i - 5 : i;
	  if (updatePosition(_gameInfo->map, tab[idx], _gameInfo->clock) == true)
	    {
	      d = ((_speed * _gameInfo->clock->getElapsed()) > 1 ? 1
		   : (_speed * _gameInfo->clock->getElapsed()));
	      _camera.translate(dir[idx] * d);
	      ret = true;
	    }
	}
    }
  if (_gameInfo->input->isPressed(keyTab[pos * 5 + 4]))
    dropBomb();
  return (ret);
}

bool	Player::checkInput()
{
  bool		ret = false;

  if (!_multi)
    ret = checkInputSingle();
  else
    ret = checkInputMulti();
  return (ret);
}

void	Player::update()
{
  if (_end == 0 && checkInput() == false && _anim == RUN)
    {
      dynamic_cast<Model *>(_model)->getModel()->setCurrentAnim(dynamic_cast<Model *>(_model)->getModel()->getAnimationFrameNumber(0), false);
      _anim = NOTHING;
    }
}

AEntity *Player::clone(int x, int y)
{
  _isAlive = true;
  _bombStock = 1;
  _maxBomb = 1;
  _health = 1;
  _speed = 5;
  _range = 0;
  _score = 0;
  _orient = NORTH;
  _anim = NOTHING;
  _end = 0;
  _x = x + 0.5;
  _y = y + 0.5;
  _camera.setPos(glm::vec3(x, 6.0, y + 7));
  _camera.setPointView(glm::vec3(x, 0.0, y));
  _model->setRotation(glm::vec3(0.0, 0.0, 0.0));
  _model->setPos(glm::vec3(x, 0.0, y));
  _model->translate(glm::vec3(0.0, -0.5, 0.0));
  return (this);
}

Camera &Player::getCam()
{
  return (_camera);
}

void Player::setMulti(bool multi)
{
  _multi = multi;
  _camera.setPlayer(multi, _gameInfo);
}

void Player::setName(const std::string &name)
{
  _name = name;
}

const std::string &Player::getName() const
{
  return (_name);
}

int Player::getScore() const
{
  return (_score);
}
