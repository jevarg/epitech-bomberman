#ifndef IA_HPP_
# define IA_HPP_

# include "ACharacter.hpp"
# include "LuaCommunication.hpp"

class		IA : public ACharacter
{
public:
  IA(int x, int y, glm::vec4 color,
     t_gameinfo &gameInfo);
  ~IA();

  void	update();
  void	pushEntitie(int x, int y, int *cnt, int aggro, t_gameinfo &gameInfo);
  int	getResultScript(int aggro, int orient);
  void	danger_in_dir(int x, int y, int min_x, int max_x, int min_y, int max_y, int i_x, int i_y, int max_it, t_gameinfo &gameInfo, int *cnt);

private:
  LuaCommunication _lua;
  int	_level;
};

#endif
