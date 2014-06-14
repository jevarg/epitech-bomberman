//
// Save.hpp for  in /home/fritsc_h/bomberman
//
// Made by Harold Fritsch
// Login   <fritsc_h@epitech.net>
//
// Started on  Tue May  6 21:55:22 2014 Harold Fritsch
// Last update Sat Jun 14 13:41:04 2014 luc sinet
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
  std::string	&encrypt(std::string &);
  std::string	&decrypt(std::string &);
  void	saveGame(Map &, Settings &, const std::string &);
  void	loadGame(const std::string &, t_gameinfo &);
private:
  ;
};

#endif /* !SAVE_HPP */
