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

  virtual void	update(t_gameinfo &gameInfo);
  void	pushEntitie(int x, int y, int *cnt, int aggro, t_gameinfo &gameInfo);
  int	getResultScript(int aggro);

private:
  LuaCommunication _lua;
  int	_level;
};

#endif
