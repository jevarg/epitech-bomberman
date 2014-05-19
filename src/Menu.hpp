#ifndef _MENU_HPP_
# define _MENU_HPP_

# include <Game.hh>
# include <SdlContext.hh>
# include "Text.hpp"
# include "Settings.hpp"
# include "Input.hpp"
# include "GameEngine.hpp"

class Menu
{
public:
  Menu(Settings &set, Input &input);
  virtual ~Menu();

  bool	initialize();
  bool	update();
  void	draw();
  void	launch();

private:
  void	launchGame();

  gdl::SdlContext	_win;
  Input			_input;
  Settings		_set;
  gdl::Clock		_clock;
  gdl::BasicShader	_shader;
  bool			_done;
  Text			_text;
};

#endif /* _MENU_HPP_ */
