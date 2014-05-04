#ifndef _IENTITIE_H_
# define _IENTITIE_H_

enum	eType
  {
    WALL = 0
  };

class AEntitie
{
public:
  AEntitie() {}
  virtual ~AEntitie() {}

protected:
  int		_x;
  int		_y;
  eType		_type;
};

#endif /* _IENTITIE_H_ */
