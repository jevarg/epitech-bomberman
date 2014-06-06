#ifndef ABOMB_HPP_
# define ABOMB_HPP_

# include "ALivingEntity.hpp"
# include "IObject.hpp"
# include "Settings.hpp"

class		ACharacter;

class		ABomb: public ALivingEntity
{
public:
  ABomb(int x, int y, ACharacter *character, t_gameinfo *gameInfo);
  virtual ~ABomb() = 0;

  void	update();
  void	explode();
  void	takeDamages(int);

protected:
  int		_range;
  int		_power;
  int		_timeout;
  ACharacter	*_character;
};

#endif /* ! BOMB_HPP_ */
