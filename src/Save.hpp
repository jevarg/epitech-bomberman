//
// Save.hpp for  in /home/fritsc_h/bomberman
// 
// Made by Harold Fritsch
// Login   <fritsc_h@epitech.net>
// 
// Started on  Tue May  6 21:55:22 2014 Harold Fritsch
// Last update Wed May  7 22:50:52 2014 Harold Fritsch
//

#ifndef SAVE_HPP_
# define SAVE_HPP_

#include <vector>
#include <string>
#include "Container.hpp"

class	GameEngine;

class	Save
{
public:
  Save();
  ~Save();
  bool	saveGame(std::vector<Container *>::const_iterator, const std::string &);
  bool	loadGame(GameEngine *, const std::string &);
private:
  ;
};

#endif /* !SAVE_HPP */
