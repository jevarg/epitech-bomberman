#ifndef BOMB_HPP_
# define BOMB_HPP_

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
};

#endif /* ! BOMB_HPP_ */
