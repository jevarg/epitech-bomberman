#ifndef IA_HPP_
# define IA_HPP_

# include "ACharacter.hpp"
# include "LuaCommunication.hpp"

class		IA : public ACharacter
{
public:
  IA(int x, int y, t_gameinfo *gameInfo, bool thread = true);
  ~IA();

  void	update();
  void	pushEntitie(int x, int y, int *cnt, int aggro);
  int	getResultScript(int aggro, int orient);
  AEntity *clone(int x, int y);

private:
  LuaCommunication _lua;
  int	_level;
};

#endif
