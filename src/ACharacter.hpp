#ifndef ACHARACTER_HPP_
# define ACHARACTER_HPP_

# include <glm/glm.hpp>

<<<<<<< HEAD
# include <Clock.hh>
# include "LuaCommunication.hpp"
# include "ALivingEntity.hpp"
# include "AEntity.hpp"
# include "Input.hpp"
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

enum	eAnim
  {
    NOTHING = 0,
    RUN
  };

enum
  {
    SPEED_AMOUNT = 1,
    SPEED_MAX = 15,
    HEALTH_AMOUNT = 1,
    HEALTH_MAX = 3,
    BOMB_AMOUNT = 1,
    BOMB_MAX = 3,
    RANGE_AMOUNT = 1,
    RANGE_MAX = 10,
    WIN = 1,
    LOSE = 2,
  };

class	ACharacter : public ALivingEntity
{
public:
  ACharacter(int x, int y, eType type, t_gameinfo *gameInfo, bool thread = true);
  virtual ~ACharacter() = 0;

  virtual void	update() = 0;

  bool		initialize();
  bool		move(Map *map, float dirX, float dirY);
  bool		updatePosition(Map *map, eAction action, gdl::Clock *clock);
  void		dropBomb();
  void		takeDamages(int amount);

  ACharacter	&operator+=(int score);

  int		getBombStock() const;
  int		getMaxBomb() const;
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
  char		getEnd() const;
  void		setEnd(char end);

  void		destroy();
protected:
  int		_bombStock;
  int		_maxBomb;
  ABomb		*_bomb;
  int		_health;
  int		_speed;
  int		_range;
  int		_score;
  eDir		_orient;
  eAnim		_anim;
  char		_end;
=======
# include "AEntitie.hpp"
# include "Model.hpp"
# include "Bomb.hpp"

class	ACharacter : public AEntitie
{
protected:
  glm::vec4	_color;
  Model		_model;
  int		_health;
  bool		_isAlive;
  int		_bombStock;
  eBombType	_bombType;
  int		_speed;
  int		_range;
  int		_score;

public:
  ACharacter(glm::vec4 color, Model model);
  ~ACharacter();
  void		moveUp();
  void		moveDown();
  void		moveLeft();
  void		moveRight();
  void		hit();
  bool		initialize();
  virtual void	update(gdl::Clock const &, gdl::Input &);
  void		draw(gdl::AShader &shader, gdl::Clock const &clock);
  
public:
  int		getScore() const;
  bool		isAlive() const;
>>>>>>> 35c0cf39dea90a7423e4e792261ed64446d55473
};

#endif /* ! ACHARACTER_HPP_ */
