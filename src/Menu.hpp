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
# include "Console.hpp"

# define SCORE_PATH "./.scores"

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
  void	loadScore();
  void	saveScore();
  void	launchGame();

  gdl::SdlContext	_win;
  gdl::BasicShader	_textShader;
  bool			_done;
  t_gameinfo		_gameInfo;
  int			_frames;
  Console		*_console;
  std::vector<AWidget *> *_currentPanel;
  std::vector<AWidget *> _mainPanel;
  std::vector<AWidget *> _newGamePanel;
  std::vector<AWidget *> _loadGamePanel;
  std::vector<AWidget *> _importMapPanel;
  std::vector<AWidget *> _optionsPanel;
};

#endif /* _MENU_HPP_ */
