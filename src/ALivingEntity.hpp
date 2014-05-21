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
  ALivingEntity(int x, int y, eType type,
		IObject *model, t_gameinfo &gameInfo);
  virtual ~ALivingEntity() = 0;

  static void	*createAliveEntity(void *arg);

  void		aliveLoop();

  bool		isAlive() const;

  virtual bool	update(gdl::Clock const &clock, Input const &input, Map &map) = 0;

protected:
  t_gameinfo	&_gameInfo;
  pthread_t	_thread;
  bool		_isAlive;
};

#endif /* _ALIVINGENTITY_H_ */
