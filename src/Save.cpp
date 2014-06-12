#include <algorithm>
#include <ios>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "Exception.hpp"
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

void		Save::encrypt(std::string &to_encrypt)
{
  for (std::string::iterator it = to_encrypt.begin(); it != to_encrypt.end(); ++it)
    {
      if ((*it <= '9' && *it >= '0') || *it == ' ')
	*it -= 25;
      else
	throw (Exception("Decrypt error : incorrect savegame file"));
    }
}

void		Save::decrypt(std::string &to_encrypt)
{
  for (std::string::iterator it = to_encrypt.begin(); it != to_encrypt.end(); ++it)
    {
      *it += 25;
      if ((*it > '9' || *it < '0') && *it != ' ')
	throw (Exception("Decrypt error : incorrect savegame file"));
    }
}

void		Save::saveGame(Map &map, Settings &settings, const std::string &name)
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

  if (file.is_open() == false)
    throw (Exception("Failed to open save file"));
  ss << settings.getVar(MAP_WIDTH) << " " << settings.getVar(MAP_HEIGHT);
  buf = ss.str();
  encrypt(buf);
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
}

void		Save::loadGame(Map &map, Settings &settings,
			       const std::string &name, t_gameinfo &gameInfo)
{
  EntityFactory	*fact = EntityFactory::getInstance();
  v_Contcit	end = gameInfo.map->ContEnd();
  std::ifstream	file(name.c_str());
  std::string	buf;
  int		x;
  int		y;
  int		type;

  if ((file.rdstate() && std::ifstream::failbit) != 0)
    throw (Exception("Error opening " + name));
  for (v_Contcit it = gameInfo.map->ContBegin();it != end;it++)
    {
      AEntity *ent;

      while ((ent = (*it)->listFront()) != NULL)
  	ent->setDestroy();
      while ((ent = (*it)->vecFront()) != NULL)
  	ent->setDestroy();
    }
  while (gameInfo.map->clearElements() != 0);
  gameInfo.map->createContainers();
  for (bool first = true; std::getline(file, buf); first = false)
    {
      decrypt(buf);
      if (std::count(buf.begin(), buf.end(), ' ') != (first ? 1 : 2))
	throw (Exception("Error : invalid savegame file"));
      std::istringstream (buf.substr(0, buf.find_first_of(' ', 0))) >> x;
      buf.erase(0, buf.find_first_of(' ', 0) + 1);
      std::istringstream (buf.substr(0, buf.find_first_of(' ', 0))) >> y;
      if (first == true)
	{
	  settings.setVar(MAP_WIDTH, x);
	  settings.setVar(MAP_HEIGHT, y);
	}
      else
	{
	  buf.erase(0, buf.find_first_of(' ', 0) + 1);
	  std::istringstream (buf) >> type;
	  if (type >= BOT || type < 0 || type == FREE)
	    throw (Exception("Error : invalid savegame file, bad type"));
	  map.addEntity(fact->getEntity(static_cast<eType>(type), x, y));
	}
    }
  file.close();
  gameInfo.map->display();
}
