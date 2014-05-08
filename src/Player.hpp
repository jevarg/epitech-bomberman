#ifndef _PLAYER_HPP_
# define _PLAYER_HPP_

# include "ACharacter.hpp"
# include "Camera.hpp"

class		Player : public ACharacter
{
public:
  Player();
  virtual ~Player();
  void		update(gdl::Clock const &, gdl::Input &);

private:
  Camera	camera;
};

#endif /* _PLAYER_HPP_ */
