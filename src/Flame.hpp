#ifndef FLAME_HPP_
# define FLAME_HPP_

# include "ALivingEntity.hpp"
# include "ACharacter.hpp"
# include "ABomb.hpp"

enum
  {
    BOX_SCORE = 5,
    PLAYER_SCORE = 200
  };

class	Flame : public ALivingEntity
{
private:
  void setScore();

  int	_power;
  int	_range;
  eDir	_direction;
  int	_timeout;
  int	_nextFlame;
  ABomb *_bomb;

public:
  Flame(int x, int y, int power, int range, eDir direction, t_gameinfo *gameInfo, ABomb *bomb,
	bool thread = true);
  ~Flame();
  void	setFire(int x, int y, eDir direction);
  void	hurtCharacter(ACharacter *character, int power);
  void	update();
  AEntity *clone(int x, int y);

  void	increaseScore(eType type) const;

  int	getRange() const;
  eDir	getDirection() const;
};

#endif /* !FLAME_HPP_ */
