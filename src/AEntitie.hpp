#ifndef _AENTITIE_HPP_
# define _AENTITIE_HPP_

# include "AObject.hpp"

enum	eEntitieType
  {
    PLAYER,
    BOMB,
    WALL,
    BOX,
    BONUSOBJECT // OR BONUSBOX
  };

class		AEntitie : public AObject
{
public:
  AEntitie();
  virtual ~AEntitie();

  int		getXPos() const;
  int		getYPos() const;
  eEntitieType	getType() const;
  void		setXPos(const int &x);
  void		setYPos(const int &y);
  void		setType(const eEntitieType &type);

protected:
  int		_x;
  int		_y;
  eEntitieType	_type;
};

#endif /* !_AENTITIE_HPP_ */
