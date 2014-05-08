#include <cstdlib>
#include "cppLua.hpp"

int add(lua_State *l)
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

int main(int argc, char const *argv[])
{
  cppLua 	CL;

  lua_pushcfunction(CL.getState(), add);
  lua_setglobal(CL.getState(), "add");
  CL.pushCreateTable(2);
  CL.pushStringS(1, "salut");
  CL.pushIntS(2, 59);
  CL.pushSetGlobal("arg");
  CL.executeLua("main.lua");
  return 0;
}
