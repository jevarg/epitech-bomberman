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
# define MAPS_PATH "./Save/Maps/"
# define GAMES_PATH "./Sve/Games/"

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
  void	setCurrentPanel(std::vector<AWidget *> * const currentPanel);
  void	textInput(std::string &buf, unsigned int maxlen);
  void	getPlayerName(std::string &name, int playerId) const;
  void	setDone(bool done = true);
  Menu	&operator++();
  Menu	&operator--();

private:
  void	loadScore();
  void	saveScore();
  void	readDir(const std::string &dirname);
  bool	textFillBuf(std::string &buf, unsigned int maxlen, Keycode key);
  void	handleClock(int &frame, double &time, double fps);

  gdl::SdlContext	_win;
  gdl::BasicShader	_textShader;
  bool			_done;
  bool			_multi;
  t_gameinfo		_gameInfo;
  GameEngine		_gameEngine;
  int			_frames;
  Console		*_console;
  unsigned int		 _filePos;
  std::list<std::string> _filename;
  std::vector<AWidget *> *_currentPanel;
  std::vector<AWidget *> _mainPanel;
  std::vector<AWidget *> _newGamePanelSolo;
  std::vector<AWidget *> _newGamePanelMulti;
  std::vector<AWidget *> _loadGamePanel;
  std::vector<AWidget *> _importMapPanel;
  std::vector<AWidget *> _optionsPanel;
  std::vector<AWidget *> _controlsPanel;
};

#endif /* _MENU_HPP_ */
