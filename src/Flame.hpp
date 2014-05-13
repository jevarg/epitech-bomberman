#ifndef FLAME_HPP_
# define FLAME_HPP_

# include "AEntity.hpp"
# include "ACharacter.hpp"

class	Flame : public AEntity
{

public:
  Flame();
  ~Flame();
  void	hurtCharacter(ACharacter *character);
};

#endif /* !FLAME_HPP_ */
