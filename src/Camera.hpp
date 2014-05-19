#ifndef _CAMERA_HPP_
# define _CAMERA_HPP_

# include <glm/glm.hpp>

class Input;

class Camera
{
public:
  Camera();
  ~Camera();

  void lookAt();
  void translate(glm::vec3 vec);
  const glm::mat4 &getTransformation() const;
  const glm::mat4 &getProjection() const;
  void	setPointView(glm::vec3 vec);

private:
  glm::mat4	_transformation;
  glm::mat4	_projection;
  glm::vec3	_pos;
  glm::vec3	_pos_view;
  glm::vec3	_dir;
};

#endif /* _CAMERA_HPP_ */
