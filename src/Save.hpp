//
// Save.hpp for  in /home/fritsc_h/bomberman
//
// Made by Harold Fritsch
// Login   <fritsc_h@epitech.net>
//
// Started on  Tue May  6 21:55:22 2014 Harold Fritsch
// Last update Sat Jun 14 14:32:40 2014 luc sinet
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
  std::string	&encrypt(std::string &) const;
  void	saveGame(const Map &, const Settings &,
		 const std::string &) const;
  void	loadGame(const std::string &,
		 t_gameinfo &) const;
private:
  ;
};

#endif /* !SAVE_HPP */
