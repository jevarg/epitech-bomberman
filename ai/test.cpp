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
