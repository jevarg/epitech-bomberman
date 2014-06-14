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
# include "Intro.hpp"
# include "Chicken.hpp"

# define SCORE_PATH "./.scores"
# define MAPS_PATH "./Save/Maps/"
# define GAMES_PATH "./Save/Games/"

class Menu
{
public:
  Menu();
  virtual ~Menu();

  bool	initialize();
  bool	update();
  void	draw();
  void	launch();
  void	launchGame(const std::string &file);
  void	setCurrentPanel(std::vector<AWidget *> * const currentPanel);
  void	textInput(std::string &buf, unsigned int maxlen);
  void	getPlayerName(std::string &name, int playerId) const;
  int	getNbIa();
  void	setDone(bool done = true);
  void	setFullScreen(const Settings * const set);
  Menu	&operator++();
  Menu	&operator--();

private:
  void	loadScore();
  void	saveScore();
  void	readDir(const std::string &dirname);
  bool	textFillBuf(std::string &buf, unsigned int maxlen, Keycode key);
  void	handleClock(int &frame, double &time, double fps);
  int	pauseMenu();

  gdl::SdlContext	_win;
  gdl::BasicShader	_textShader;
  bool			_done;
  bool			_multi;
  t_gameinfo		_gameInfo;
  GameEngine		_gameEngine;
  int			_frames;
  Cube			_cube;
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
  std::vector<AWidget *> _screenPanel;
  std::vector<AWidget *> _pausePanel;
  std::vector<AWidget *> _savePanel;
  Player		 *_player1;
  Player		 *_player2;
};

#endif /* _MENU_HPP_ */
