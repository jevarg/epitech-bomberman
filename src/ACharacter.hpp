#ifndef ACHARACTER_HPP_
# define ACHARACTER_HPP_

# include <glm/glm.hpp>

# include "AEntity.hpp"
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

class	ACharacter : public AEntity
{
protected:
  pthread_t	_thread;
  Mutex		_mutex;
  Condvar	_condvar;
  glm::vec4	_color;
  int		_health;
  bool		_isAlive;
  int		_bombStock;
  ABomb		*_bomb;
  int		_speed;
  int		_range;
  int		_score;
  eDir		_orient;

public:
  ACharacter(int x, int y, glm::vec4 color, IObject *model);
  virtual ~ACharacter() = 0;

  virtual bool	update(gdl::Clock const &clock, Input const &input, Map &map) = 0;

  bool		updatePosition(Map &map, eAction action);
  bool		initialize();
  bool		move(Map &map, int dirX, int dirY);
  void		takeDamages(int amount);

  int		getScore() const;
  bool		isAlive() const;

  int		getSpeed() const;
  int		getHealth() const;
  void		setSpeed(int speed);
  void		setHealth(int health);
};

void	*handle_character_thread(void *arg);

#endif /* ! ACHARACTER_HPP_ */
