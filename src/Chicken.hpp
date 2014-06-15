#ifndef CHICKEN_H_
# define CHICKEN_H_

# include "ACharacter.hpp"

class		Chicken : public ACharacter
{
public:
  Chicken(int x, int y, t_gameinfo *gameInfo, bool thread = true);
  ~Chicken();

  void	update();
  void	pushEntitie(int x, int y, int *cnt, int aggro);
  int	getResultScript(int orient, const char * fileName);
  AEntity *clone(int, int);
  void	takeDamages(int);

private:
  LuaCommunication _lua;
};

#endif
