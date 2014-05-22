#ifndef _ALIVINGENTITY_H_
# define _ALIVINGENTITY_H_

# include "AEntity.hpp"
# include "Mutex.hpp"
# include "Condvar.hpp"
# include "Input.hpp"
# include "Settings.hpp"

typedef struct s_gameinfo	t_gameinfo;

class ALivingEntity : public AEntity
{
public:
  ALivingEntity(int x, int y, eType type, t_gameinfo &gameInfo);
  virtual ~ALivingEntity() = 0;

  void		aliveLoop();
  void		setDead();
  bool		isAlive() const;

  void		destroy(Map &map);
  virtual void	update(t_gameinfo &gameInfo) = 0;

protected:
  t_gameinfo	&_gameInfo;
  pthread_t	_thread;
  bool		_isAlive;
};

void	*createAliveEntity(void *arg);

#endif /* _ALIVINGENTITY_H_ */
