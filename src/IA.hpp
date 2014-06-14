#ifndef IA_HPP_
# define IA_HPP_

# include "ACharacter.hpp"
# include "Flame.hpp"

class		IA : public ACharacter
{
public:
  IA(int x, int y, t_gameinfo *gameInfo, bool thread = true);
  ~IA();

  void	update();
  void	pushEntitie(int x, int y, int *cnt, int aggro);
  int	getResultScript(int aggro, int orient, const char * fileName);
  void	danger_in_dir(int i, int j, int x, int y,
		      int i_x, int i_y, int max_it, int *cnt);
  void	put_abstract_flame(Flame *ff, int i, int j, int c1, int c2, int *cnt);

  virtual AEntity *clone(int, int);

private:
  LuaCommunication _lua;
  int	_level;
};

#endif
