#ifndef _TRANSFORMATION_HPP_
# define _TRANSFORMATION_HPP_

# include <glm/glm.hpp>
# include <glm/gtc/matrix_transform.hpp>

class ATransformation
{
public:
  ATransformation();
<<<<<<< HEAD
  virtual ~ATransformation() = 0;

  void translate(glm::vec3 const &v);
  void rotate(glm::vec3 const& axis, float angle);
  void scale(glm::vec3 const& scale);
  void setPos(glm::vec3 const& pos);
  void setScale(glm::vec3 const& scale);
  void setRotation(glm::vec3 const& rot);

  const glm::vec3 &getPos() const;
=======
  void translate(glm::vec3 const &v);
  void rotate(glm::vec3 const& axis, float angle);
  void scale(glm::vec3 const& scale);
>>>>>>> 35c0cf39dea90a7423e4e792261ed64446d55473
  const glm::mat4 getTransformation() const;

protected:
  glm::vec3 _position;
  glm::vec3 _rotation;
  glm::vec3 _scale;
};

#endif /* _TRANSFORMATION_HPP_ */
