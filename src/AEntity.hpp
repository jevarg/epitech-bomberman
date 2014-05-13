#ifndef _AENTITIE_HPP_
# define _AENTITIE_HPP_

# include <Clock.hh>
# include <BasicShader.hh>
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
  AEntity(int x, int y, eType type, IObject *model);
  virtual ~AEntity();

  int		getXPos() const;
  int		getYPos() const;
  eType		getType() const;
  void		setXPos(const int &x);
  void		setYPos(const int &y);
  void		setType(const eType &type);
  void		draw(gdl::AShader &shader, gdl::Clock &clock);

protected:
  int		_x;
  int		_y;
  eType		_type;
  IObject	*_model;
};

#endif /* !_AENTITIE_HPP_ */
