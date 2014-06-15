#include "ATransformation.hpp"

ATransformation::ATransformation(): _position(0, 0, 0), _rotation(0, 0, 0), _scale(1, 1, 1)
{

}

<<<<<<< HEAD
ATransformation::~ATransformation()
{
}

=======
>>>>>>> 35c0cf39dea90a7423e4e792261ed64446d55473
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

<<<<<<< HEAD
void ATransformation::setPos(glm::vec3 const& pos)
{
  _position = pos;
}

void ATransformation::setRotation(glm::vec3 const& rot)
{
  _rotation = rot;
}

void ATransformation::setScale(glm::vec3 const& scale)
{
  _scale = scale;
}

const glm::vec3 &ATransformation::getPos() const
{
  return (_position);
}

=======
>>>>>>> 35c0cf39dea90a7423e4e792261ed64446d55473
const glm::mat4 ATransformation::getTransformation() const
{
  glm::mat4 transform(1);

<<<<<<< HEAD
  transform = glm::translate(transform, _position);
  if (_rotation.x)
    transform = glm::rotate(transform, _rotation.x, glm::vec3(1, 0, 0));
  if (_rotation.y)
    transform = glm::rotate(transform, _rotation.y, glm::vec3(0, 1, 0));
  if ( _rotation.z)
    transform = glm::rotate(transform, _rotation.z, glm::vec3(0, 0, 1));
  if (_scale != glm::vec3(1.0, 1.0, 1.0))
    transform = glm::scale(transform, _scale);
=======
  transform = glm::rotate(transform, _rotation.x, glm::vec3(1, 0, 0));
  transform = glm::rotate(transform, _rotation.y, glm::vec3(0, 1, 0));
  transform = glm::rotate(transform, _rotation.z, glm::vec3(0, 0, 1));
  transform = glm::translate(transform, _position);
  transform = glm::scale(transform, _scale);
>>>>>>> 35c0cf39dea90a7423e4e792261ed64446d55473
  return (transform);
}
