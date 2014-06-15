#include "GameEngine.hpp"
<<<<<<< HEAD
#include "Input.hpp"
#include "Camera.hpp"

Camera::Camera(t_gameinfo *gameinfo, bool player): _pos(0.0, 0.0, 0.0), _pos_view(0.0, 0.0, 1.0), _dir(0.0, 1.0, 0.0)
{
  float nbPlayer = (player == false) ? 1 : 2;

  _projection = glm::perspective(static_cast<float>(gameinfo->set->getVar(FOV)),
				 (static_cast<float>(gameinfo->set->getVar(W_WIDTH)) / nbPlayer)
				 / (static_cast<float>(gameinfo->set->getVar(W_HEIGHT))),
				 0.1f, 100.0f);
=======
#include "Camera.hpp"

Camera::Camera()
{
  _projection = glm::perspective(CFOV, DEF_SIZE_X / DEF_SIZE_Y, 0.1f, 100.0f);
>>>>>>> 35c0cf39dea90a7423e4e792261ed64446d55473
}


Camera::~Camera()
{

}

<<<<<<< HEAD
void	Camera::lookAt()
{
  _transformation = glm::lookAt(_pos, _pos_view, _dir);
}

void	Camera::translate(glm::vec3 vec)
{
  _pos += vec;
  _pos_view += vec;
=======
bool	Camera::initialize()
{
  _pos_view = glm::vec3(1.0, 0.0, 0.0);
  _dir = glm::vec3(0.0, 1.0, 0.0);
  return (true);
}

void Camera::update(gdl::Clock const &clock, gdl::Input &in)
{
  if (in.getKey(SDLK_q))
    {
      _position += (glm::vec3(2.0, 0.0, 0.0) * static_cast<float>(clock.getElapsed()) * 10.0f);
      _pos_view += (glm::vec3(2.0, 0.0, 0.0) * static_cast<float>(clock.getElapsed()) * 10.0f);
    }
  if (in.getKey(SDLK_d))
    {
      _position -= (glm::vec3(2.0, 0.0, 0.0) * static_cast<float>(clock.getElapsed()) * 10.0f);
      _pos_view -= (glm::vec3(2.0, 0.0, 0.0) * static_cast<float>(clock.getElapsed()) * 10.0f);
    }
  if (in.getKey(SDLK_z))
    {
      _position += (glm::vec3(0.0, 0.0, 2.0) * static_cast<float>(clock.getElapsed()) * 10.0f);
      _pos_view += (glm::vec3(0.0, 0.0, 2.0) * static_cast<float>(clock.getElapsed()) * 10.0f);
    }
  if (in.getKey(SDLK_s))
    {
      _position -= (glm::vec3(0.0, 0.0, 2.0) * static_cast<float>(clock.getElapsed()) * 10.0f);
      _pos_view -= (glm::vec3(0.0, 0.0, 2.0) * static_cast<float>(clock.getElapsed()) * 10.0f);
    }
  if (in.getKey(SDLK_UP))
    {
      _position += (glm::vec3(0.0, 2.0, 0.0) * static_cast<float>(clock.getElapsed()) * 10.0f);
      _pos_view += (glm::vec3(0.0, 2.0, 0.0) * static_cast<float>(clock.getElapsed()) * 10.0f);
    }
  if (in.getKey(SDLK_DOWN))
    {
      _position -= (glm::vec3(0.0, 2.0, 0.0) * static_cast<float>(clock.getElapsed()) * 10.0f);
      _pos_view -= (glm::vec3(0.0, 2.0, 0.0) * static_cast<float>(clock.getElapsed()) * 10.0f);
    }
}

void	Camera::lookAt()
{
  _transformation = glm::lookAt(_position, _pos_view, _dir);
>>>>>>> 35c0cf39dea90a7423e4e792261ed64446d55473
}

const glm::mat4 &Camera::getTransformation() const
{
  return (_transformation);
}

const glm::mat4	&Camera::getProjection() const
{
  return (_projection);
}
<<<<<<< HEAD

void	Camera::setPointView(glm::vec3 vec)
{
  _pos_view = vec;
}

const glm::vec3	&Camera::getPosView() const
{
  return (_pos_view);
}

void	Camera::setPos(glm::vec3 pos)
{
  _pos = pos;
}

void	Camera::setPlayer(bool player, t_gameinfo *gameInfo)
{
  float nbPlayer = (player == false) ? 1 : 2;

  _projection = glm::perspective(static_cast<float>(gameInfo->set->getVar(FOV)),
  				 (static_cast<float>(gameInfo->set->getVar(W_WIDTH)) / nbPlayer)
  				 / (static_cast<float>(gameInfo->set->getVar(W_HEIGHT))),
  				 0.1f, 100.0f);
}
=======
>>>>>>> 35c0cf39dea90a7423e4e792261ed64446d55473
