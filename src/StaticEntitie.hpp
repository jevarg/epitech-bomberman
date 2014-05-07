#ifndef _STATICENTITIE_HPP_
# define _STATICENTITIE_HPP_

# include "AEntitie.hpp"

class StaticEntitie : public AEntitie
{
public:
  explicit StaticEntitie(eType type);
  ~StaticEntitie();
};

#endif /* !_STATICENTITIE_HPP_ */
