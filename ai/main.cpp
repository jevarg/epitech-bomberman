/*

**

*/

#include "cppLua.hpp"

int main(int argc, char const *argv[])
{
  cppLua 	CL;

  CL.pushCreateTable(2);
  CL.pushStringS(1, "salut");
  CL.pushIntS(2, 59);
  CL.pushSetGlobal("arg");
  CL.executeLua("main.lua");
  return 0;
}
