#include "cppLua.hpp"

cppLua::cppLua()
{
  _luaState = luaL_newstate();
  static luaL_Reg lualibs[] =
    {
      {"base", luaopen_base},
      {"io", luaopen_io},
      {"string", luaopen_string},
      {"math", luaopen_math},
      {"table", luaopen_table},
      {NULL, NULL}
    };
  const luaL_Reg *lib = lualibs;
  while (lib->func != NULL)
    {
      luaL_requiref(_luaState, lib->name, lib->func, 1);
      lua_settop(_luaState, 0);
      ++lib;
    }
}

cppLua::~cppLua()
{
  lua_close(_luaState);
}

void	cppLua::pushCreateTable(const int nb)
{
  lua_createtable(_luaState, nb, 0);
}

void  cppLua::pushIntString(const int index, const char *val) const
{
  lua_pushnumber(_luaState, index);
  lua_pushstring(_luaState, val);
  lua_settable(_luaState, -3);
}

void  cppLua::pushStringString(const char *index, const char *val) const
{
  lua_pushstring(_luaState, index);
  lua_pushstring(_luaState, val);
  lua_settable(_luaState, -3);
}

void  cppLua::pushIntInt(const int index, const int val) const
{
  lua_pushnumber(_luaState, index);
  lua_pushnumber(_luaState, val);
  lua_settable(_luaState, -3);
}

void  cppLua::pushStringInt(const char *index, const int val) const
{
  lua_pushstring(_luaState, index);
  lua_pushnumber(_luaState, val);
  lua_settable(_luaState, -3);
}

void	cppLua::pushSetGlobal(const char *name) const
{
  lua_setglobal(_luaState, name);
}

void	cppLua::executeLua(const char *name)
{
  if ((_status = luaL_loadfile(_luaState, name)) == LUA_OK)
    lua_pcall(_luaState, 0, LUA_MULTRET, 0);
}

lua_State* cppLua::getState() const
{
  return (_luaState);
}
