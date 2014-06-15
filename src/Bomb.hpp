#ifndef BOMB_HPP_
# define BOMB_HPP_

<<<<<<< HEAD
# include "ABomb.hpp"
# include "ACharacter.hpp"
# include "IObject.hpp"

class		Bomb: public ABomb
{
public:
  Bomb(int x, int y, ACharacter *character, t_gameinfo *gameInfo, bool thread = true);
  virtual ~Bomb();
  AEntity *clone(int x, int y);

private:
  pthread_t	_thread;
  Mutex		_mutex;
=======
enum	eBombType
  {
    NORMAL,
    BONUS
  };

class		Bomb
{
public:
  Bomb();
  ~Bomb();

private:
  eBombType	_type;
  int		_range;
>>>>>>> 35c0cf39dea90a7423e4e792261ed64446d55473
};

#endif /* ! BOMB_HPP_ */
