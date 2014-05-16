#ifndef _TRANSFORMATION_HPP_
# define _TRANSFORMATION_HPP_

# include <glm/glm.hpp>
# include <glm/gtc/matrix_transform.hpp>

class ATransformation
{
public:
  ATransformation();
  void translate(glm::vec3 const &v);
  void rotate(glm::vec3 const& axis, float angle);
  void scale(glm::vec3 const& scale);
  const glm::mat4 getTransformation() const;

protected:
  glm::vec3 _position;
  glm::vec3 _rotation;
  glm::vec3 _scale;
};

#endif /* _TRANSFORMATION_HPP_ */