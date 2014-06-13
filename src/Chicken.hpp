#ifndef CHICKEN_H_
# define CHICKEN_H_

# include "ACharacter.hpp"
# include "LuaCommunication.hpp"

class		Chicken : public ACharacter
{
public:
  Chicken(int x, int y, t_gameinfo *gameInfo, bool thread = true);
  ~Chicken();

  void	update();
  void	pushEntitie(int x, int y, int *cnt, int aggro);
  int	getResultScript(const char * fileName);
  virtual AEntity *clone(int, int);

private:
  LuaCommunication _lua;
};

#endif
