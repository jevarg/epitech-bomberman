#ifndef _AENTITY_HPP_
# define _AENTITY_HPP_

# include <Clock.hh>
# include <BasicShader.hh>
# include "IObject.hpp"
# include "Input.hpp"
# include "Model.hpp"

typedef struct s_gameinfo       t_gameinfo;

enum	eType
  {
    WALL = 0,
    FREE,
    BOX,
    BOMB,
    FLAME,
    ITEM,
    CHARACTER,
    GROUND,
    UNKNOWNENTITY
  };

class Map;

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
  AEntity(t_gameinfo &gameInfo);
  AEntity(int x, int y, eType type, t_gameinfo &gameInfo);
  virtual ~AEntity() = 0;

  int		getXPos() const;
  int		getYPos() const;
  eType		getType() const;
  void		setXPos(const int &x);
  void		setYPos(const int &y);
  void		setType(const eType &type);
  void		setDestroy();
  bool		toDestroy() const;
  void		draw(gdl::AShader &shader, gdl::Clock &clock);
  virtual void	destroy(Map &map) = 0;
  virtual void	takeDamages(int amount) = 0;

protected:
  int		_x;
  int		_y;
  eType		_type;
  t_gameinfo	&_gameInfo;
  bool		_toDestroy;
  IObject	*_model;
};

void	*handle_character_thread(void *arg);

#endif /* !_AENTITY_HPP_ */
