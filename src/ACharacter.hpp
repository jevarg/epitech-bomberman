#ifndef ACHARACTER_HPP_
# define ACHARACTER_HPP_

# include <glm/glm.hpp>

# include "AEntitie.hpp"
# include "Model.hpp"
# include "Bomb.hpp"

class	ACharacter : public AEntitie
{
protected:
  glm::vec4	_color;
  Model		_model;
  int		_bombStock;
  int		_score;
  int		_speed;
  int		_range;
  eBombType	_bombType;

public:
  ACharacter(glm::vec4 color, Model model);
  ~ACharacter();
  void		moveUp();
  void		moveDown();
  void		moveLeft();
  void		moveRight();
  bool		initialize();
  virtual void	update(gdl::Clock const &, gdl::Input &);
  void		draw(gdl::AShader &shader, gdl::Clock const &clock);

public:
  int		getScore();

};

#endif /* ! ACHARACTER_HPP_ */
