#include <algorithm>
#include <ios>
#include <iostream>
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

bool		Save::encrypt(std::string &to_encrypt)
{
  for (std::string::iterator it = to_encrypt.begin(); it != to_encrypt.end(); ++it)
    {
      if ((*it < '9' && *it > '0') || *it == ' ')
	*it -= 25;
      else
	{
	  std::cerr << "Error : incorrect savegame file" << std::endl;
	  return (false);
	}
    }
  return (true);
}

bool		Save::decrypt(std::string &to_encrypt)
{
  for (std::string::iterator it = to_encrypt.begin(); it != to_encrypt.end(); ++it)
    {
      *it += 25;
      if ((*it > '9' || *it < '0') && *it != ' ')
      	{
      	  std::cerr << "Error : incorrect savegame file" << std::endl;
      	  return (false);
      	}
    }
  return (true);
}

bool		Save::saveGame(Map &map, const std::string &name)
{
  std::ofstream	file(name.c_str());
  std::string	buf;

  buf = "42 12 1337";
  this->encrypt(buf);
  for (int it = 0; it < 1000; ++it)
    {
      file << buf << "\n";
    }
  file.close();
  return (true);
}

bool		Save::loadGame(Map &map, const std::string &name)
{
  std::ifstream	file(name.c_str());
  std::string	buf;
  int		x;
  int		y;
  int		type;

  if ((file.rdstate() & std::ifstream::failbit) != 0)
    {
      std::cerr << "Error opening " << name << "\n";
      return (false);
    }
  while (std::getline(file, buf))
    {
      this->decrypt(buf);
      if (std::count(buf.begin(), buf.end(), ' ') != 2)
	{
	  std::cerr << "Error : invalid savegame file" << std::endl;
	  return (false);
	}
      std::istringstream (buf.substr(0, buf.find_first_of(' ', 0))) >> x;
      buf.erase(0, buf.find_first_of(' ', 0) + 1);
      std::istringstream (buf.substr(0, buf.find_first_of(' ', 0))) >> y;
      buf.erase(0, buf.find_first_of(' ', 0) + 1);
      std::istringstream (buf) >> type;
      map.addEntitie(new AEntitie(x, y, static_cast<eType>(type)));
      std::cout << "x : " << x << " y : " << y << " type : " << type << std::endl;
    }
  file.close();
  return (true);
}
