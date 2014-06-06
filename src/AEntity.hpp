#ifndef _AENTITY_HPP_
# define _AENTITY_HPP_

# include <Clock.hh>
# include <BasicShader.hh>
# include "IObject.hpp"
# include "Input.hpp"
# include "Model.hpp"
# include "Mutex.hpp"

typedef struct s_gameinfo       t_gameinfo;

enum	eType
  {
    WALL = 0,
    FREE,
    BOX,
    BOMB,
    FLAME,
    ITEM,
    SPEEDITEM,
    HEALTHITEM,
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
  AEntity(t_gameinfo *gameInfo);
  AEntity(int x, int y, eType type, t_gameinfo *gameInfo);
  virtual ~AEntity() = 0;

  int		getXPos() const;
  int		getYPos() const;
  eType		getType() const;
  void		setXPos(const int &x);
  void		setYPos(const int &y);
  void		setType(const eType &type);
  bool		toDestroy() const;
  void		draw(gdl::AShader &shader, gdl::Clock &clock);
  int		getDeathTime() const;
  void		decTimeDeath();

  virtual void	setDestroy();
  virtual void	destroy();

  virtual void	takeDamages(int amount) = 0;

protected:
  float		_x;
  float		_y;
  eType		_type;
  t_gameinfo	*_gameInfo;
  Mutex		*_mutex;
  bool		_toDestroy;
  int		_timeDeath;
  int		_time;
  IObject	*_model;
};

void	*handle_character_thread(void *arg);

#endif /* !_AENTITY_HPP_ */
