#ifndef _PLAYER_HPP_
# define _PLAYER_HPP_

# include "ACharacter.hpp"
# include "Camera.hpp"

class		Player : public ACharacter
{
public:
  Player(int x, int y, t_gameinfo *gameInfo, eType type, bool thread = true);
  virtual ~Player();
  bool	checkInput();
  bool	checkInputSingle();
  bool	checkInputMulti();
  void	update();
  Camera &getCam();
  AEntity *clone(int x, int y);

private:
  Camera	_camera;
};

#endif /* _PLAYER_HPP_ */
