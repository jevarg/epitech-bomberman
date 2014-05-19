#ifndef ACHARACTER_HPP_
# define ACHARACTER_HPP_

# include <glm/glm.hpp>

# include "AEntity.hpp"
# include "Model.hpp"
# include "Bomb.hpp"
# include "Mutex.hpp"
# include "Condvar.hpp"
# include "Input.hpp"
# include "Settings.hpp"

class Input;

enum	e_dir
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
  eBombType	_bombType;
  int		_speed;
  int		_range;
  int		_score;
  e_dir		_orient;

public:
  ACharacter(int x, int y, glm::vec4 color, IObject *model);
  ~ACharacter();
  bool		initialize();
  virtual void	update(gdl::Clock const &clock, Input const &input, Map &map) = 0;

public:
  bool		move(eAction, Map &map);
  void		hit();

public:
  int		getScore() const;
  bool		isAlive() const;
};

void	*handle_thread(void *arg);

#endif /* ! ACHARACTER_HPP_ */
