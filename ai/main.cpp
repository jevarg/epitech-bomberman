#include <cstdlib>
#include "cppLua.hpp"
#include "test.hpp"

int main(int argc, char const *argv[])
{
  cppLua 	CL;
  test		t;

  lua_pushcfunction(CL.getState(), t.add);
  lua_setglobal(CL.getState(), "add");
  CL.pushCreateTable(2);
  CL.pushStringS(1, "salut");
  CL.pushIntS(2, 59);
  CL.pushSetGlobal("arg");
  CL.executeLua("main.lua");
  return 0;
}
