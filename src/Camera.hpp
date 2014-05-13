#ifndef _CAMERA_HPP_
# define _CAMERA_HPP_

# include <glm/glm.hpp>
# include <Input.hh>

class Camera : public ATransformation
{
public:
  Camera();
  ~Camera();

  bool initialize();
  void update(gdl::Clock const &, Input &);
  void lookAt();
  const glm::mat4 &getTransformation() const;
  const glm::mat4 &getProjection() const;

private:
  glm::mat4	_transformation;
  glm::mat4	_projection;
  glm::vec3	_pos_view;
  glm::vec3	_dir;
};

#endif /* _CAMERA_HPP_ */
