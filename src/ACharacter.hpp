#ifndef ACHARACTER_HPP_
# define ACHARACTER_HPP_

# include <glm/glm.hpp>

# include "ALivingEntity.hpp"
# include "Model.hpp"
# include "Bomb.hpp"

class Input;

enum	eDir
  {
    NORTH = 0,
    WEST,
    SOUTH,
    EAST,
    ALLDIR
  };

class	ACharacter : public ALivingEntity
{
public:
  ACharacter(int x, int y, glm::vec4 color, t_gameinfo &gameInfo);
  virtual ~ACharacter() = 0;

  virtual void	update() = 0;

  bool		initialize();
  bool		move(Map &map, int dirX, int dirY);
  bool		updatePosition(Map &map, eAction action);
  void		dropBomb(t_gameinfo &gameInfo);
  void		takeDamages(int amount);

  int		getBombStock() const;
  void		setBombStock(int bombStock);
  ABomb		*getBomb() const;
  void		setBomb(ABomb *bomb);
  int		getHealth() const;
  void		setHealth(int health);
  int		getSpeed() const;
  void		setSpeed(int speed);
  int		getRange() const;
  void		setRange(int range);
  int		getScore() const;

protected:
  glm::vec4	_color;
  int		_bombStock;
  ABomb		*_bomb;
  int		_health;
  int		_speed;
  int		_range;
  int		_score;
  eDir		_orient;
};

#endif /* ! ACHARACTER_HPP_ */
