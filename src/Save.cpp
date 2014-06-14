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

std::string    	&Save::encrypt(std::string &to_encrypt)
{
  for (std::string::iterator it = to_encrypt.begin(); it != to_encrypt.end(); ++it)
    {
      if ((*it <= '9' && *it >= '0') || *it == ' ')
	*it -= 25;
      else
	throw (Exception("Decrypt error : incorrect savegame file"));
    }
  return (to_encrypt);
}

std::string    	&Save::decrypt(std::string &to_encrypt)
{
  for (std::string::iterator it = to_encrypt.begin(); it != to_encrypt.end(); ++it)
    {
      *it += 25;
      if ((*it > '9' || *it < '0') && *it != ' ')
	throw (Exception("Decrypt error : incorrect savegame file"));
    }
  return (to_encrypt);
}

void		Save::saveGame(Map &map, Settings &settings, const std::string &name)
{
  v_Contcit	it;
  v_Contcit	end;
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
  for (it = map.ContBegin(), end = map.ContEnd();
       it != end; ++it)
    {
      for (vit = (*it)->vecBegin(), vit_end = (*it)->vecEnd();
	   vit != vit_end; ++vit)
	{
	  std::ostringstream	oss;
	  oss << (*vit)->getXPos() << " " << (*vit)->getYPos() << " "
	      << static_cast<int>((*vit)->getType());
	  buf = oss.str();
	  file << encrypt(buf) << std::endl;
	}
      for (lit = (*it)->listBegin(), lit_end = (*it)->listEnd();
	     lit != lit_end; ++lit)
	{
	  std::ostringstream	oss;
	  oss << (*lit)->getXPos() << " " << (*lit)->getYPos() << " "
	      << static_cast<int>((*lit)->getType());
	  buf = oss.str();
	  file << encrypt(buf) << std::endl;
	}
    }
  file.close();
}

void		Save::loadGame(const std::string &name, t_gameinfo &gameInfo)
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
	  gameInfo.set->setVar(MAP_WIDTH, x);
	  gameInfo.set->setVar(MAP_HEIGHT, y);
	}
      else
	{
	  buf.erase(0, buf.find_first_of(' ', 0) + 1);
	  std::istringstream (buf) >> type;
	  if (type >= BOT || type < 0 || type == FREE)
	    throw (Exception("Error : invalid savegame file, bad type"));
	  gameInfo.map->addEntity(fact->getEntity(static_cast<eType>(type), x, y));
	}
    }
  file.close();
  gameInfo.map->display();
}
