#ifndef _IENTITIE_H_
# define _IENTITIE_H_

enum	eType
  {
    WALL = 0,
    BOX,
    FREE,
    GROUND,
  };

typedef struct	s_entity
{
  s_entity(int x, int y, eType type) : _x(x), _y(y), _type(type)
  {
  }
  int		_x;
  int		_y;
  eType		_type;
}		t_entity;

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
