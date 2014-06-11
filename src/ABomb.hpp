#ifndef ABOMB_HPP_
# define ABOMB_HPP_

# include "ALivingEntity.hpp"
# include "IObject.hpp"
# include "Settings.hpp"

# define MIN_RANGE 2

class		ACharacter;

class		ABomb: public ALivingEntity
{
public:
  ABomb(int x, int y, ACharacter *character, t_gameinfo *gameInfo, bool thread = true);
  virtual ~ABomb() = 0;

  void		update();
  void		explode();
  void		takeDamages(int);
  int		getRange() const;
  void		setRange(int range);
  void		destroy();
  ACharacter	*getCharacter();

protected:
  int		_range;
  int		_power;
  int		_timeout;
  ACharacter	*_character;
};

#endif /* ! BOMB_HPP_ */
