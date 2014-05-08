#include <sstream>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "GameEngine.hpp"
#include "Save.hpp"
#include "Container.hpp"

Save::Save()
{
  ;
}

Save::~Save()
{
  ;
}

bool		Save::saveGame(std::vector<Container *>::const_iterator it, const std::string &name)
{
  std::ofstream	file(name.c_str());

  file << "ouais";
  file.close();
  return (true);
}

bool		Save::loadGame(GameEngine *gameEngine, const std::string &name)
{
  std::ifstream	file(name.c_str());
  std::stringstream ss("");
  std::string	buf;
  int		x;
  int		y;
  int		type;

  ss << file.rdbuf();
  buf = ss.str();
  // x << buf;
  // y << buf;
  // type << buf;
  // std::cout << "x : " << x << " y : " << y << " type : " << type << std::endl;
  file.close();
  return (true);
}
