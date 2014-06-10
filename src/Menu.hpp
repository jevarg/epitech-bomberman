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
# include "AWidget.hpp"

class Menu
{
public:
  Menu();
  virtual ~Menu();

  bool	initialize();
  bool	update();
  void	draw();
  void	launch();
  void	setCurrentPanel(std::vector<AWidget *> *currentPanel);

private:
  void	launchGame();

  gdl::SdlContext	_win;
  gdl::BasicShader	_textShader;
  bool			_done;
  t_gameinfo		_gameInfo;
  int			_frames;
  std::vector<AWidget *> *_currentPanel;
  std::vector<AWidget *> _mainPanel;
  std::vector<AWidget *> _loadPanel;
  std::vector<AWidget *> _optionPanel;
};

#endif /* _MENU_HPP_ */
