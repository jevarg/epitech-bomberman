#ifndef SAVE_HPP_
# define SAVE_HPP_

#include <vector>
#include <string>
#include "Container.hpp"
#include "Map.hpp"
#include "Settings.hpp"
#include "EntityFactory.hpp"

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
  void	checkDirectory(const std::string &) const;
};

#endif /* !SAVE_HPP */
