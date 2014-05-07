#ifndef ACHARACTER_HPP_
# define ACHARACTER_HPP_

#include <glm/glm.hpp>
#include "AEntitie.hpp"
#include "Model.hpp"
#include "Bomb.hpp"

class	ACharacter : public AEntitie
{
protected:
  glm::vec4	_color;
  Model		_model;
  int		_bombNb;
  int		_score;
  int		_speed;
  int		_range;
  eBombType	_bombType;

public:
  ACharacter();
  ~ACharacter();
  void		moveForward();
  void		moveBackward();
  void		moveLeft();
  void		moveRight();
  bool		initialize();
  void		draw();

public:
  virtual bool	update() const = 0;

public:
  int		getScore();

};

#endif /* ! ACHARACTER_HPP_ */
