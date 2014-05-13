#ifndef ACHARACTER_HPP_
# define ACHARACTER_HPP_

# include <glm/glm.hpp>

# include "AEntity.hpp"
# include "Model.hpp"
# include "Bomb.hpp"
# include "Mutex.hpp"
# include "Condvar.hpp"
# include "Settings.hpp"

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

public:
  ACharacter(int x, int y, glm::vec4 color, IObject *model);
  ~ACharacter();
  bool		initialize();
  virtual void	update(gdl::Clock const &, Input &);
  void		draw(gdl::AShader &shader, gdl::Clock const &clock);

public:
  void		move(eAction);
  void		hit();

public:
  int		getScore() const;
  bool		isAlive() const;
};

void	*handle_thread(void *arg);

#endif /* ! ACHARACTER_HPP_ */
