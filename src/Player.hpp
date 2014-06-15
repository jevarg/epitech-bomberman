
#ifndef _PLAYER_HPP_
# define _PLAYER_HPP_

# include "ACharacter.hpp"
# include "Camera.hpp"

class		Player : public ACharacter
{
public:
  Player(int x, int y, t_gameinfo *gameInfo, eType type, bool multi = false, bool thread = true);
  virtual ~Player();
  bool	checkInput();
  bool	checkInputSingle();
  bool	checkInputMulti();
  void	update();
  Camera &getCam();
  AEntity *clone(int x, int y);
  void  setMulti(bool multi);
  void	setName(const std::string &name);
  const std::string &getName() const;
  int getScore() const;

private:
  Camera	_camera;
  bool		_multi;
  std::string	_name;
};

#endif /* _PLAYER_HPP_ */
