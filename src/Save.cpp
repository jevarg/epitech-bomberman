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
#include "Settings.hpp"

 Save::Save()
 {
 }

 Save::~Save()
 {
 }

 bool		Save::encrypt(std::string &to_encrypt)
 {
   for (std::string::iterator it = to_encrypt.begin(); it != to_encrypt.end(); ++it)
     {
       if ((*it <= '9' && *it >= '0') || *it == ' ')
	 *it -= 25;
       else
	 {
	   std::cerr << "Encrypt error : incorrect savegame file" << std::endl;
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
	   std::cerr << "Decrypt error : incorrect savegame file" << std::endl;
	   return (false);
	 }
     }
   return (true);
 }

 bool		Save::saveGame(Map &map, Settings &settings, const std::string &name)
 {
   std::vector<Container *>::const_iterator	it = map.ContBegin();
   std::vector<Container *>::const_iterator	end = map.ContEnd();
   v_Entcit	vit;
   v_Entcit	vit_end;
   l_Entcit     	lit;
   l_Entcit     	lit_end;
   std::ofstream	file(name.c_str());
   std::string	buf;
   std::ostringstream	ss;

  ss << settings.getVar(MAP_WIDTH) << " " << settings.getVar(MAP_HEIGHT);
  buf = ss.str();
  this->encrypt(buf);
  file << buf << "\n";
  buf = "";
  while (it != end)
    {
      vit = (*it)->vecBegin();
      vit_end = (*it)->vecEnd();
      while (vit != vit_end)
	{
	  std::ostringstream	oss;
	  oss << (*vit)->getXPos() << " " << (*vit)->getYPos() << " "
	      << static_cast<int>((*vit)->getType());
	  buf = oss.str();
	  this->encrypt(buf);
	  file << buf << "\n";
	  ++vit;
	  buf = "";
	}
      lit = (*it)->listBegin();
      lit_end = (*it)->listEnd();
      while (lit != lit_end)
	{
	  std::ostringstream	oss;
	  oss << (*lit)->getXPos() << " " << (*lit)->getYPos() << " "
	      << static_cast<int>((*lit)->getType());
	  buf = oss.str();
	  this->encrypt(buf);
	  file << buf << "\n";
	  ++lit;
	  buf = "";
	}
      ++it;
    }
  file.close();
  return (true);
}

bool		Save::loadGame(Map &map, Settings &settings,
			       const std::string &name)
{
  std::ifstream	file(name.c_str());
  std::string	buf;
  int		line = 0;
  int		x;
  int		y;
  int		type;
  EntityFactory	*fact = EntityFactory::getInstance();

  if ((file.rdstate() && std::ifstream::failbit) != 0)
    {
      std::cerr << "Error opening " << name << "\n";
      return (false);
    }
  if (std::getline(file, buf))
    {
      if (this->decrypt(buf) == false)
	    {
	      std::cerr << "Error : invalid savegame file on line : " << line << std::endl;
	      return (false);
	    }
      if (std::count(buf.begin(), buf.end(), ' ') != 1)
	{
	  std::cerr << "Error : invalid savegame file" << std::endl;
	  return (false);
	}
      std::istringstream (buf.substr(0, buf.find_first_of(' ', 0))) >> x;
      buf.erase(0, buf.find_first_of(' ', 0) + 1);
      std::istringstream (buf.substr(0, buf.find_first_of(' ', 0))) >> y;
      settings.setVar(MAP_WIDTH, x);
      settings.setVar(MAP_HEIGHT, y);
      while (std::getline(file, buf))
	{
	  if (this->decrypt(buf) == false)
	    {
	      std::cerr << "Error : invalid savegame file on line : " << line << std::endl;
	      return (false);
	    }
	  std::cout << "readed : " << buf << std::endl;
	  if (std::count(buf.begin(), buf.end(), ' ') != 2)
	    {
	      std::cerr << "Error : invalid savegame file on line : " << line << std::endl;
	      return (false);
	    }
	  std::istringstream (buf.substr(0, buf.find_first_of(' ', 0))) >> x;
	  buf.erase(0, buf.find_first_of(' ', 0) + 1);
	  std::istringstream (buf.substr(0, buf.find_first_of(' ', 0))) >> y;
	  buf.erase(0, buf.find_first_of(' ', 0) + 1);
	  std::istringstream (buf) >> type;
	  if (type >= UNKNOWNENTITY || type < 0)
	    {
	      std::cerr << "Error : invalid savegame file on line : " << line << std::endl;
	      return (false);
	    }
	  map.addEntity(fact->getEntity(static_cast<eType>(type % (GROUND + 1)), x, y));
	  ++line;
	}
    }
  file.close();
  return (true);
}
