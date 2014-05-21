#ifndef ACHARACTER_HPP_
# define ACHARACTER_HPP_

# include <glm/glm.hpp>

# include "ALivingEntity.hpp"
# include "AEntity.hpp"
# include "Input.hpp"
# include "Model.hpp"
# include "ABomb.hpp"
# include "Mutex.hpp"
# include "Condvar.hpp"
# include "Input.hpp"
# include "Settings.hpp"

class Input;

enum	eDir
  {
    NORTH = 0,
    WEST,
    SOUTH,
    EAST,
  };

class	ACharacter : public ALivingEntity
{
public:
  ACharacter(int x, int y, glm::vec4 color, IObject *model,
	     t_gameinfo &gameInfo);
  virtual ~ACharacter() = 0;

  virtual bool	update(gdl::Clock const &clock, Input const &input, Map &map) = 0;

  bool		initialize();
  bool		move(Map &map, int dirX, int dirY);
  bool		updatePosition(Map &map, eAction action);

  int		getScore() const;
  int		getSpeed() const;
  int		getHealth() const;
  void		setSpeed(int speed);
  void		setHealth(int health);

protected:
  glm::vec4	_color;
  int		_health;
  int		_bombStock;
  ABomb		*_bomb;
  int		_speed;
  int		_range;
  int		_score;
  eDir		_orient;
};

#endif /* ! ACHARACTER_HPP_ */
