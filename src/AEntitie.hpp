#ifndef _IENTITIE_H_
# define _IENTITIE_H_

enum	eType
  {
    WALL = 0,
    BOX,
    FREE
  };

class AEntitie
{
public:
  AEntitie();
  AEntitie(int x, int y, eType type);
  virtual ~AEntitie();

  int	getXPos() const;
  int	getYPos() const;
  eType	getType() const;

protected:
  int		_x;
  int		_y;
  eType		_type;
};

#endif /* _IENTITIE_H_ */
