#include "ATransformation.hpp"

ATransformation::ATransformation(): _position(0, 0, 0), _rotation(0, 0, 0), _scale(1, 1, 1)
{

}

ATransformation::~ATransformation()
{
}

void ATransformation::translate(glm::vec3 const &v)
{
  _position += v;
}

void ATransformation::rotate(glm::vec3 const& axis, float angle)
{
  _rotation += axis * angle;
}

void ATransformation::scale(glm::vec3 const& scale)
{
  _scale *= scale;
}

const glm::vec3 &ATransformation::getPos() const
{
  return (_position);
}

const glm::mat4 ATransformation::getTransformation() const
{
  glm::mat4 transform(1);

  transform = glm::translate(transform, _position);
  transform = glm::rotate(transform, _rotation.x, glm::vec3(1, 0, 0));
  transform = glm::rotate(transform, _rotation.y, glm::vec3(0, 1, 0));
  transform = glm::rotate(transform, _rotation.z, glm::vec3(0, 0, 1));
  transform = glm::scale(transform, _scale);
  return (transform);
}
