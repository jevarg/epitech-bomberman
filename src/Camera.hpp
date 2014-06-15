#ifndef _CAMERA_HPP_
# define _CAMERA_HPP_

# include <glm/glm.hpp>
<<<<<<< HEAD

typedef struct s_gameinfo t_gameinfo;
class Input;

class Camera
{
public:
  Camera(t_gameinfo *gameInfo, bool player = false);
  ~Camera();

  void lookAt();
  void translate(glm::vec3 vec);
  void	setPointView(glm::vec3 vec);
  void	setPos(glm::vec3 pos);

  void	setPlayer(bool player, t_gameinfo *gameInfo);

  const glm::mat4 &getTransformation() const;
  const glm::mat4 &getProjection() const;
  const glm::vec3 &getPosView() const;
=======
# include <Input.hh>

class Camera : public ATransformation
{
public:
  Camera();
  ~Camera();

  bool initialize();
  void update(gdl::Clock const &, gdl::Input &);
  void lookAt();
  const glm::mat4 &getTransformation() const;
  const glm::mat4 &getProjection() const;

  void	update(gdl::Input &in);
>>>>>>> 35c0cf39dea90a7423e4e792261ed64446d55473

private:
  glm::mat4	_transformation;
  glm::mat4	_projection;
<<<<<<< HEAD
  glm::vec3	_pos;
=======
>>>>>>> 35c0cf39dea90a7423e4e792261ed64446d55473
  glm::vec3	_pos_view;
  glm::vec3	_dir;
};

#endif /* _CAMERA_HPP_ */
