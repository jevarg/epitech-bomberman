#include "LuaCommunication.hpp"

LuaCommunication::LuaCommunication()
{
  _luaState = luaL_newstate();
  luaL_openlibs(_luaState);
}

LuaCommunication::~LuaCommunication()
{
  lua_close(_luaState);
}

void	LuaCommunication::pushCreateTable(const int nb)
{
  lua_createtable(_luaState, nb, 0);
}

void  LuaCommunication::pushIntString(const int index, const char *val) const
{
  lua_pushnumber(_luaState, index);
  lua_pushstring(_luaState, val);
  lua_settable(_luaState, -3);
}

void  LuaCommunication::pushStringString(const char *index, const char *val) const
{
  lua_pushstring(_luaState, index);
  lua_pushstring(_luaState, val);
  lua_settable(_luaState, -3);
}

void  LuaCommunication::pushIntInt(const int index, const int val) const
{
  lua_pushnumber(_luaState, index);
  lua_pushnumber(_luaState, val);
  lua_settable(_luaState, -3);
}

void  LuaCommunication::pushStringInt(const char *index, const int val) const
{
  lua_pushstring(_luaState, index);
  lua_pushnumber(_luaState, val);
  lua_settable(_luaState, -3);
}

void	LuaCommunication::pushSetGlobal(const char *name) const
{
  lua_setglobal(_luaState, name);
}

void	LuaCommunication::executeLua(const char *name)
{
  if ((_status = luaL_loadfile(_luaState, name)) == LUA_OK)
    lua_pcall(_luaState, 0, LUA_MULTRET, 0);
}

lua_State* LuaCommunication::getState() const
{
  return (_luaState);
}

void LuaCommunication::popStack() const
{
  lua_pop(_luaState, 1);
}

void LuaCommunication::getDatas()
{
  std::stringstream str_buf;

  while(lua_gettop(_luaState))
    {
      switch(lua_type(_luaState, lua_gettop(_luaState)))
        {
        case LUA_TNUMBER:
	  str_buf << "script returned the number: "
		  << lua_tonumber(_luaState, lua_gettop(_luaState));
	  break;
        }
      lua_pop(_luaState, 1);
      std::cout << str_buf.str() << std::endl;
      str_buf.str("");
    }
}
