#include <cstdlib>
#include "test.hpp"

test::test()
{
}

test::~test()
{
}

int test::getX() const
{
  return (_x);
}

int test::getY() const
{
  return (_y);
}

void test::setX(int x)
{
  _x = x;
}

void test::setY(int y)
{
  _y = y;
}

int test::add(lua_State *l)
{
  int ac = lua_gettop(l);
  int i = 0;
  int x = 0;
  int y = 0;

  x = std::atoi(lua_tostring(l, lua_gettop(l)));
  lua_pop(l, 1);
  y = std::atoi(lua_tostring(l, lua_gettop(l)));
  lua_pop(l, 1);

  lua_pushnumber(l, x + y);
  return (1);
}
