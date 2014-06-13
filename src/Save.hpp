//
// Save.hpp for  in /home/fritsc_h/bomberman
//
// Made by Harold Fritsch
// Login   <fritsc_h@epitech.net>
//
// Started on  Tue May  6 21:55:22 2014 Harold Fritsch
// Last update Thu Jun 12 22:42:40 2014 Harold Fritsch
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
  void	encrypt(std::string &);
  void	decrypt(std::string &);
  void	saveGame(Map &, Settings &, const std::string &);
  void	loadGame(const std::string &, t_gameinfo &);
private:
  ;
};

#endif /* !SAVE_HPP */
