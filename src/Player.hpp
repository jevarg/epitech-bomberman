#ifndef _PLAYER_HPP_
# define _PLAYER_HPP_

# include "ACharacter.hpp"
# include "Camera.hpp"

class		Player : public ACharacter
{
public:
  Player(int x, int y, Camera *camera, glm::vec4 color, t_gameinfo &gameInfo);
  virtual ~Player();

  void	checkInput(t_gameinfo &gameInfo);
  void	update(t_gameinfo &gameInfo);
private:
  Camera	*_camera;
};

#endif /* _PLAYER_HPP_ */
