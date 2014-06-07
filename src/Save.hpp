//
// Save.hpp for  in /home/fritsc_h/bomberman
//
// Made by Harold Fritsch
// Login   <fritsc_h@epitech.net>
//
// Started on  Tue May  6 21:55:22 2014 Harold Fritsch
// Last update Sat Jun  7 02:00:13 2014 
//

#ifndef SAVE_HPP_
# define SAVE_HPP_

#include <vector>
#include <string>
#include "Container.hpp"
#include "Map.hpp"
#include "Settings.hpp"
#include "EntityFactory.hpp"

class	GameEngine;

class	Save
{
public:
  Save();
  ~Save();
  bool	encrypt(std::string &);
  bool	decrypt(std::string &);
  bool	saveGame(Map &, Settings &, const std::string &);
  bool	loadGame(Map &, Settings &, const std::string &);
private:
  ;
};

#endif /* !SAVE_HPP */
