#ifndef _MENU_HPP_
# define _MENU_HPP_

# include <Game.hh>
# include <SdlContext.hh>
# include <vector>
# include "Settings.hpp"
# include "Input.hpp"
# include "GameEngine.hpp"
# include "Text.hpp"
# include "Sound.hpp"
/*# include "Widget.hpp"*/

class Menu
{
public:
  Menu(Settings &set);
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
  gdl::BasicShader	_textShader;
  bool			_done;
  Text			_text;
  Sound			_sound;
  int			_frames;
  // std::vector<Widget>	_mainPanel;
  // std::vector<Widget>	_loadPanel;
  // std::vector<Widget>	_optionPanel;
};

#endif /* _MENU_HPP_ */
