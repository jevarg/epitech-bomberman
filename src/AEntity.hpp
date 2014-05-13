#ifndef _AENTITY_HPP_
# define _AENTITY_HPP_

# include "IObject.hpp"

enum	eType
  {
    WALL = 0,
    BOX,
    FREE,
    FLAME,
    CHARACTER,
    GROUND,
    UNKNOWNENTITY
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

class		AEntity
{
public:
  AEntity();
  AEntity(int x, int y, eType type);
  virtual ~AEntity();

  int		getXPos() const;
  int		getYPos() const;
  eType		getType() const;
  void		setXPos(const int &x);
  void		setYPos(const int &y);
  void		setType(const eType &type);

protected:
  int		_x;
  int		_y;
  eType		_type;
};

#endif /* !_AENTITY_HPP_ */
