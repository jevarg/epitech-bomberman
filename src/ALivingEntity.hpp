#ifndef _ALIVINGENTITY_H_
# define _ALIVINGENTITY_H_

# include "AEntity.hpp"
# include "Mutex.hpp"
# include "Condvar.hpp"
# include "Input.hpp"
# include "Settings.hpp"

class ALivingEntity : public AEntity
{
public:
  ALivingEntity(int x, int y, eType type,
		IObject *model, Condvar &condvar, Mutex &mutex);
  virtual ~ALivingEntity() = 0;

  static void	*createAliveEntity(void *arg);

  void		aliveLoop();

  bool		isAlive() const;

  virtual bool	update(gdl::Clock const &clock, Input const &input, Map &map) = 0;

protected:
  Mutex		&_mutex;
  Condvar	&_condvar;
  bool		_isAlive;
};

#endif /* _ALIVINGENTITY_H_ */
