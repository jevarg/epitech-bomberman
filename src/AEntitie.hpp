#ifndef _AENTITIE_H_
# define _AENTITIE_H_

enum	eType
  {
    PLAYER,
    BOMB,
    WALL,
    BOX,
    BONUS
  };

class AEntitie
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

#endif /* _AENTITIE_H_ */
