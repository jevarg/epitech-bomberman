#ifndef IA_HPP_
# define IA_HPP_

# include "ACharacter.hpp"
# include "LuaCommunication.hpp"

class		IA : public ACharacter
{
public:
  IA(int x, int y, t_gameinfo *gameInfo, bool thread = false);
  ~IA();

  void	update();
  void	pushEntitie(int x, int y, int *cnt, int aggro);
  int	getResultScript(int aggro, int orient);
  void	danger_in_dir(int x, int y, int min_x, int max_x, int min_y,
		      int max_y, int i_x, int i_y, int max_it, int *cnt);

  virtual AEntity *clone(int, int);

private:
  LuaCommunication _lua;
  int	_level;
};

#endif
