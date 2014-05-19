#include "GameEngine.hpp"
#include "Input.hpp"
#include "Camera.hpp"

Camera::Camera(): _pos(0.0, 0.0, 0.0), _pos_view(0.0, 0.0, 1.0), _dir(0.0, 1.0, 0.0)
{
  _projection = glm::perspective(CFOV, DEF_SIZE_X / DEF_SIZE_Y, 0.1f, 100.0f);
}


Camera::~Camera()
{

}

void	Camera::lookAt()
{
  _transformation = glm::lookAt(_pos, _pos_view, _dir);
}

void	Camera::translate(glm::vec3 vec)
{
  _pos += vec;
  _pos_view += vec;
}

const glm::mat4 &Camera::getTransformation() const
{
  return (_transformation);
}

const glm::mat4	&Camera::getProjection() const
{
  return (_projection);
}

void	Camera::setPointView(glm::vec3 vec)
{
  _pos_view = vec;
}
