//
// test.hpp for head in /home/collin_b/project/c++/bomberman/bomberman/ai
// 
// Made by jonathan.collinet
// Login   <collin_b@epitech.net>
// 
// Started on  Thu May  8 19:42:10 2014 jonathan.collinet
// Last update Thu May  8 20:05:37 2014 jonathan.collinet
//

#ifndef TEST_HPP
# define TEST_HPP

#include <lua.hpp>

class		test
{
public:
  test();
  ~test();

  int getX() const;
  int getY() const;

  void setX(int);
  void setY(int);

  int add(lua_State *l);

private:
  int	_x;
  int	_y;
};

#endif
