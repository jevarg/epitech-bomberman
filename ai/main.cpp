#include <cstdlib>
#include "cppLua.hpp"
#include "test.hpp"

int main(int argc, char const *argv[])
{
  cppLua 	CL;
  test		t;

  CL.pushCreateTable(3);
  CL.pushIntString(1, "salut");
  CL.pushStringString("yo", "salut");
  CL.pushIntInt(2, 59);
  CL.pushSetGlobal("arg");
  CL.executeLua("main.lua");
  return 0;
}
