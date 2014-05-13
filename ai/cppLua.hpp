//
// cpp_lua.hpp for head in /home/collin_b/project/c++/test_lua_c++/test
// 
// Made by jonathan.collinet
// Login   <collin_b@epitech.net>
// 
// Started on  Thu May  8 17:17:14 2014 jonathan.collinet
// Last update Thu May  8 20:02:25 2014 jonathan.collinet
//

#ifndef CPPLUA_
# define CPPLUA_

# include <lua.hpp>
# include <iostream>

class cppLua
{
public:
  cppLua();
  ~cppLua();

  void	pushCreateTable(const int nb);
  void  pushIntString(const int index, const char *val) const;
  void  pushStringString(const char *index, const char *val) const;
  void  pushIntInt(const int index, const int val) const;
  void  pushStringInt(const char *index, const int val) const;
  void	pushSetGlobal(const char *name) const;
  void	executeLua(const char *name);

  lua_State* getState() const;

private:
  lua_State*	_luaState;
  int 		_status;
};

#endif
