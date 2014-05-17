#include "GameEngine.hpp"
#include "Input.hpp"
#include "Camera.hpp"

Camera::Camera()
{
  _projection = glm::perspective(CFOV, DEF_SIZE_X / DEF_SIZE_Y, 0.1f, 100.0f);
}


Camera::~Camera()
{

}

bool	Camera::initialize()
{
  _pos_view = glm::vec3(0.0, 0.0, 1.0);
  _dir = glm::vec3(0.0, 1.0, 0.0);
  return (true);
}

void Camera::update(gdl::Clock const &clock, Input &in)
{
  if (in[LEFT])
    {
      _position += (glm::vec3(2.0, 0.0, 0.0) * static_cast<float>(clock.getElapsed()) * 10.0f);
      _pos_view += (glm::vec3(2.0, 0.0, 0.0) * static_cast<float>(clock.getElapsed()) * 10.0f);
    }
  if (in[RIGHT])
    {
      _position -= (glm::vec3(2.0, 0.0, 0.0) * static_cast<float>(clock.getElapsed()) * 10.0f);
      _pos_view -= (glm::vec3(2.0, 0.0, 0.0) * static_cast<float>(clock.getElapsed()) * 10.0f);
    }
  if (in[FORWARD])
    {
      _position += (glm::vec3(0.0, 0.0, 2.0) * static_cast<float>(clock.getElapsed()) * 10.0f);
      _pos_view += (glm::vec3(0.0, 0.0, 2.0) * static_cast<float>(clock.getElapsed()) * 10.0f);
    }
  if (in[BACK])
    {
      _position -= (glm::vec3(0.0, 0.0, 2.0) * static_cast<float>(clock.getElapsed()) * 10.0f);
      _pos_view -= (glm::vec3(0.0, 0.0, 2.0) * static_cast<float>(clock.getElapsed()) * 10.0f);
    }
  // if (in[SDLK_UP))
  //   {
  //     _position += (glm::vec3(0.0, 2.0, 0.0) * static_cast<float>(clock.getElapsed()) * 10.0f);
  //     _pos_view += (glm::vec3(0.0, 2.0, 0.0) * static_cast<float>(clock.getElapsed()) * 10.0f);
  //   }
  // if (in[SDLK_DOWN))
  //   {
  //     _position -= (glm::vec3(0.0, 2.0, 0.0) * static_cast<float>(clock.getElapsed()) * 10.0f);
  //     _pos_view -= (glm::vec3(0.0, 2.0, 0.0) * static_cast<float>(clock.getElapsed()) * 10.0f);
  //   }
}

void	Camera::lookAt()
{
  _transformation = glm::lookAt(_position, _pos_view, _dir);
}

const glm::mat4 &Camera::getTransformation() const
{
  return (_transformation);
}

const glm::mat4	&Camera::getProjection() const
{
  return (_projection);
}
