<<<<<<< HEAD
=======
//
// Save.hpp for  in /home/fritsc_h/bomberman
// 
// Made by Harold Fritsch
// Login   <fritsc_h@epitech.net>
// 
// Started on  Tue May  6 21:55:22 2014 Harold Fritsch
// Last update Thu May  8 18:47:27 2014 Harold Fritsch
//

>>>>>>> 35c0cf39dea90a7423e4e792261ed64446d55473
#ifndef SAVE_HPP_
# define SAVE_HPP_

#include <vector>
#include <string>
#include "Container.hpp"
#include "Map.hpp"
<<<<<<< HEAD
#include "Settings.hpp"
#include "EntityFactory.hpp"
=======

class	GameEngine;
>>>>>>> 35c0cf39dea90a7423e4e792261ed64446d55473

class	Save
{
public:
  Save();
  ~Save();
<<<<<<< HEAD
  std::string	&encrypt(std::string &) const;
  void	saveGame(const Map &, const Settings &,
		 const std::string &) const;
  void	loadGame(const std::string &,
		 t_gameinfo &) const;
private:
  void	checkDirectory(const std::string &) const;
=======
  bool	encrypt(std::string &);
  bool	decrypt(std::string &);
  bool	saveGame(Map &, const std::string &);
  bool	loadGame(Map &, const std::string &);
private:
  ;
>>>>>>> 35c0cf39dea90a7423e4e792261ed64446d55473
};

#endif /* !SAVE_HPP */
