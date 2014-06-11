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
  void	launchGame();
  void	setCurrentPanel(std::vector<AWidget *> *currentPanel);
  void	textInput(std::string &buf, unsigned int maxlen, int x, int y);
  void	setDone(bool done = true);

private:
  void	loadScore();
  void	saveScore();
  void	readDir(const std::string &dirname);
  void	textFillBuf(std::string &buf, unsigned int maxlen, Keycode key);
  void	handleClock(int &frame, double &time, double fps);

  gdl::SdlContext	_win;
  gdl::BasicShader	_textShader;
  bool			_done;
  t_gameinfo		_gameInfo;
  int			_frames;
  Console		*_console;
  std::list<std::string> _filename;
  std::vector<AWidget *> *_currentPanel;
  std::vector<AWidget *> _mainPanel;
  std::vector<AWidget *> _newGamePanel;
  std::vector<AWidget *> _loadGamePanel;
  std::vector<AWidget *> _importMapPanel;
  std::vector<AWidget *> _optionsPanel;
  std::vector<AWidget *> _controlsPanel;
};

#endif /* _MENU_HPP_ */
