#ifndef FLAME_HPP_
# define FLAME_HPP_

# include "AEntitie.hpp"
# include "ACharacter.hpp"

class	Flame : public AEntitie
{

public:
  Flame();
  ~Flame();
  void	hurtCharacter(ACharacter *character);
};

#endif /* !FLAME_HPP_ */
