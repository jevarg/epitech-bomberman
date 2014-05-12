#ifndef _MENU_HPP_
# define _MENU_HPP_

# include <Game.hh>
# include <SdlContext.hh>
# include "GameEngine.hpp"

class Menu
{
public:
  Menu();
  virtual ~Menu();

  bool	initialize();
  bool	update();
  void	draw();
  void	launch();

private:
  void	launchGame();

  gdl::SdlContext	_win;
  gdl::Input		_input;
  gdl::Clock		_clock;
  gdl::BasicShader	_shader;
  bool			_done;
};

#endif /* _MENU_HPP_ */
