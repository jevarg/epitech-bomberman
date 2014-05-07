#ifndef _AENTITIE_HPP_
# define _AENTITIE_HPP_

# include "AObject.hpp"

enum	eType
  {
    PLAYER,
    BOMB,
    WALL,
    BOX,
    BONUSOBJECT // OR BONUSBOX
  };

class	AEntitie : public AObject
{
public:
  AEntitie();
  virtual ~AEntitie();

  int	getXPos() const;
  int	getYPos() const;
  eType	getType() const;

protected:
  int		_x;
  int		_y;
  eType		_type;
};

#endif /* !_AENTITIE_HPP_ */
