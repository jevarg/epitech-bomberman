#include <algorithm>
#include <iostream>
#include <sstream>
#include <fstream>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "GameEngine.hpp"
#include "Menu.hpp"
#include "Exception.hpp"
#include "Save.hpp"

Save::Save()
{
}

Save::~Save()
{
}

std::string    	&Save::encrypt(std::string &to_encrypt) const
{
  char		Key = 'k';

  for (std::string::iterator it = to_encrypt.begin(); it != to_encrypt.end(); ++it)
    *it ^= Key;
  return (to_encrypt);
}

void		Save::checkDirectory(const std::string &path) const
{
  struct stat	st;

  if (stat(path.c_str(), &st) == -1)
    mkdir(path.c_str(), 0755);
}

void		Save::saveGame(const Map &map, const Settings &settings,
			       const std::string &name) const
{
  v_Contcit	it;
  v_Contcit	end;
  v_Entcit	vit;
  v_Entcit	vit_end;
  l_Entcit     	lit;
  l_Entcit     	lit_end;
  std::string	buf;
  std::ostringstream	ss;

  checkDirectory("./Save");
  checkDirectory(MAPS_PATH);
  checkDirectory(GAMES_PATH);
  std::ofstream	file(name.c_str());
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

void		Save::loadGame(const std::string &name,
			       t_gameinfo &gameInfo) const
{
  EntityFactory	*fact = EntityFactory::getInstance();
  std::ifstream	file(name.c_str());
  std::string	buf;
  v_Contcit	end;
  int		x;
  int		y;
  int		type;

  if ((file.rdstate() && std::ifstream::failbit) != 0)
    throw (Exception("Error opening " + name));
  if (gameInfo.map) // erase old entities
    {
      for (v_Contcit it = gameInfo.map->ContBegin(), end = gameInfo.map->ContEnd();
	   it != end; it++)
	{
	  AEntity *ent;

	  while ((ent = (*it)->listFront()) != NULL)
	    ent->setDestroy();
	  while ((ent = (*it)->vecFront()) != NULL)
	    ent->setDestroy();
      }
      while (gameInfo.map->clearElements() != 0);
    }
  else
    gameInfo.map = new Map(*gameInfo.set);
  gameInfo.map->createContainers();
  for (bool first = true; std::getline(file, buf); first = false)
    {
      encrypt(buf);
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
	  if (type > BOT || type < 0 || type == FREE)
	    throw (Exception("Error : invalid savegame file, bad type"));
	  std::cout << "TYPE => " << static_cast<eType>(type) << std::endl;
	  gameInfo.map->addEntity(fact->getEntity(static_cast<eType>(type), x, y));
	}
    }
  file.close();
  gameInfo.map->display();
}
