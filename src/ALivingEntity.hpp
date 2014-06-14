#ifndef _ALIVINGENTITY_H_
# define _ALIVINGENTITY_H_

# include "AEntity.hpp"
# include "Condvar.hpp"
# include "Input.hpp"
# include "Settings.hpp"

typedef struct s_gameinfo	t_gameinfo;

class ALivingEntity : public AEntity
{
public:
  ALivingEntity(int x, int y, eType type, t_gameinfo *gameInfo, bool thread = true);
  virtual ~ALivingEntity() = 0;

  void		aliveLoop();
  void		setDead();
  bool		isAlive() const;

  void		setDestroyAttr();
  virtual void	update() = 0;
  virtual bool	die();
  virtual void 	destroy();
  virtual void	takeDamages(int amount);
  void		setDestroy();

protected:
  pthread_t	_thread;
  bool		_isAlive;
};

void	*createAliveEntity(void *arg);

#endif /* _ALIVINGENTITY_H_ */
