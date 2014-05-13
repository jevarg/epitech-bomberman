#ifndef _PLAYER_HPP_
# define _PLAYER_HPP_

# include "ACharacter.hpp"
# include "Camera.hpp"
# include "Input.hpp"

class		Player : public ACharacter
{
public:
  Player(Camera camera, glm::vec4 color, Model model);
  virtual ~Player();

  void		update(gdl::Clock const &, Input &);

private:
  Camera	_camera;
};

#endif /* _PLAYER_HPP_ */
