#ifndef _PLAYER_HPP_
# define _PLAYER_HPP_

# include "ACharacter.hpp"
# include "Camera.hpp"
# include "Input.hpp"

class		Player : public ACharacter
{
public:
  Player(int x, int y, Camera *camera, glm::vec4 color,
	 t_gameinfo &gameInfo, int id);
  virtual ~Player();
  bool	checkInput();
  bool	checkInputSingle();
  bool	checkInputMulti();
  void	update();

private:
  Camera	*_camera;
  int		_id;
};

#endif /* _PLAYER_HPP_ */
