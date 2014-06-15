<<<<<<< HEAD

=======
>>>>>>> 35c0cf39dea90a7423e4e792261ed64446d55473
#ifndef _PLAYER_HPP_
# define _PLAYER_HPP_

# include "ACharacter.hpp"
# include "Camera.hpp"

class		Player : public ACharacter
{
public:
<<<<<<< HEAD
  Player(int x, int y, t_gameinfo *gameInfo, eType type, bool multi = false, bool thread = true);
  virtual ~Player();
  bool	checkInput();
  bool	checkInputSingle();
  bool	checkInputMulti();
  void	update();
  Camera &getCam();
  AEntity *clone(int x, int y);
  void setMulti(bool multi);

private:
  Camera	_camera;
  bool		_multi;
=======
  Player(Camera camera, glm::vec4 color, Model model);
  virtual ~Player();

  void		update(gdl::Clock const &, gdl::Input &);

private:
  Camera	_camera;
>>>>>>> 35c0cf39dea90a7423e4e792261ed64446d55473
};

#endif /* _PLAYER_HPP_ */
