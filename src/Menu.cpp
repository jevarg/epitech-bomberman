#include <iostream>
#include <fstream>
#include <sstream>
#include <sys/types.h>
#include <dirent.h>
#include "Menu.hpp"
#include "NavigationWidget.hpp"
#include "ImageWidget.hpp"
#include "InputWidget.hpp"
#include "LaunchWidget.hpp"
#include "QuitWidget.hpp"
#include "LoadWidget.hpp"
#include "LoadGameWidget.hpp"
#include "ArrowWidget.hpp"
#include "KeyWidget.hpp"

Menu::Menu(): _win(), _textShader(), _done(false), _gameInfo(NULL, NULL, NULL, NULL, NULL, NULL)
{
  _frames = 0;
  _gameInfo.input = new Input();
  _gameInfo.set = new Settings();
  _gameInfo.sound = new Sound();
  _gameInfo.clock = new gdl::Clock();
  _gameInfo.set->loadFile(DEFAULT_FILE);
  _gameInfo.set->loadFile(USER_FILE);
  loadScore();

  _currentPanel = &_mainPanel;
  _console = new Console(*_gameInfo.set, *_gameInfo.input, *_gameInfo.clock, _textShader);
  //    _console->aff(*_gameInfo.clock, _textShader, _win, *_gameInfo.input);
}

Menu::~Menu()
{
  saveScore();
}

bool  Menu::initialize()
{
  int x = _gameInfo.set->getVar(W_WIDTH), y = _gameInfo.set->getVar(W_HEIGHT);

  if (!_win.start(x, y, "Bomberman"))
    throw(Exception("Cannot open window"));
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  if (!_textShader.load("./Shaders/text.fp", GL_FRAGMENT_SHADER) ||
      !_textShader.load("./Shaders/text.vp", GL_VERTEX_SHADER) ||
      !_textShader.build())
    return (false);
  _gameInfo.sound->play("menu", MUSIC);
  ImageWidget	*background = new ImageWidget(0, 0, y, x,
					      "./Ressources/Images/background.tga");
  ImageWidget	*title = new ImageWidget(x / 8, y / 1.43f, y / 4.8f, x / 1.3f,
					 "./assets/BomberCraft.tga");
  NavigationWidget *back = new NavigationWidget(x / 8, y / 11.25f, y / 11.25f, x / 6.15f,
						"./assets/Button/back.tga", &_mainPanel);

  _mainPanel.push_back(background);
  _mainPanel.push_back(title);
  _mainPanel.push_back(new NavigationWidget(x / 4, y / 1.8f, y / 11.25f, x / 2,
					    "./assets/Button/singleplayer.tga", &_newGamePanel));
  _mainPanel.push_back(new NavigationWidget(x / 4, y / 2.25f, y / 11.25f, x / 2,
					    "./assets/Button/multiplayer.tga", &_newGamePanel));
  _mainPanel.push_back(new NavigationWidget(x / 4, y / 3.0f, y / 11.25f, x / 2,
					    "./assets/Button/load_game.tga", &_loadGamePanel));
  _mainPanel.push_back(new NavigationWidget(x / 4, y / 4.5f, y / 11.25f, x / 2,
					    "./assets/Button/options.tga", &_optionsPanel));
  _mainPanel.push_back(new QuitWidget(x / 4, y / 18, y / 11.25f, x / 2,
				      "./assets/Button/quit.tga"));

  ///  _mainPanel.push_back(new InputWidget(50, 50, y / 11.25f, x / 2, "allotest"));

  _newGamePanel.push_back(background);
  _newGamePanel.push_back(title);
  _newGamePanel.push_back(back);
  _newGamePanel.push_back(new LaunchWidget(x / 4, 450, y / 11.25f, x / 2,
					   "./assets/Button/generate_map.tga", &_mainPanel));
  _newGamePanel.push_back(new NavigationWidget(x / 4, 300, y / 11.25f, x / 2,
					       "./assets/Button/import_map.tga", &_importMapPanel));

  _loadGamePanel.push_back(background);
  _loadGamePanel.push_back(title);
  _loadGamePanel.push_back(back);
  _loadGamePanel.push_back(new LoadGameWidget(x / 4, y / 1.8f, y / 11.25f, x / 2,
					       "./assets/Button/button.tga", "Free", 0));
  _loadGamePanel.push_back(new LoadGameWidget(x / 4, y / 2.25f, y / 11.25f, x / 2,
					       "./assets/Button/button.tga", "Free", 1));
  _loadGamePanel.push_back(new LoadGameWidget(x / 4, y / 3.0f, y / 11.25f, x / 2,
					       "./assets/Button/button.tga", "Free", 2));
  _loadGamePanel.push_back(new LoadGameWidget(x / 4, y / 4.5f, y / 11.25f, x / 2,
					       "./assets/Button/button.tga", "Free", 3));
  _loadGamePanel.push_back(new ArrowWidget(x / 2 - 2 * (x / 21.0f), y / 11.25f, y / 12, x / 21.0f,
					    "./assets/Button/left_arrow.tga", 0));
  _loadGamePanel.push_back(new ArrowWidget(x / 2 + x / 21.0f, y / 11.25f, y / 12, x / 21.0f,
					    "./assets/Button/right_arrow.tga", 1));


  // add input widget or input image
  _importMapPanel.push_back(background);
  _importMapPanel.push_back(title);
  _importMapPanel.push_back(back);
  _importMapPanel.push_back(new LoadWidget(x / 4, y / 1.8f, y / 11.25f, x / 2,
					   "./assets/Button/button.tga", "Free", 0));
  _importMapPanel.push_back(new LoadWidget(x / 4, y / 2.25f, y / 11.25f, x / 2,
					   "./assets/Button/button.tga", "Free", 1));
  _importMapPanel.push_back(new LoadWidget(x / 4, y / 3.0f, y / 11.25f, x / 2,
					   "./assets/Button/button.tga", "Free", 2));
  _importMapPanel.push_back(new LoadWidget(x / 4, y / 4.5f, y / 11.25f, x / 2,
					   "./assets/Button/button.tga", "Free", 3));
  _importMapPanel.push_back(new ArrowWidget(x / 2 - 2 * (x / 21.0f), y / 11.25f, y / 12, x / 21.0f,
					    "./assets/Button/left_arrow.tga", 0));
  _importMapPanel.push_back(new ArrowWidget(x / 2 + x / 21.0f, y / 11.25f, y / 12, x / 21.0F,
					    "./assets/Button/right_arrow.tga", 1));

  // add input widget or input image
  _optionsPanel.push_back(background);
  _optionsPanel.push_back(title);
  _optionsPanel.push_back(back);
  _optionsPanel.push_back(new ImageWidget(x / 4, y / 2.25f, y / 11.25f, x / 2,
					  "./assets/Button/fullscreen_off.tga"));
  _optionsPanel.push_back(new NavigationWidget(x / 4, y / 3.0f, y / 11.25f, x / 2,
					       "./assets/Button/controls.tga", &_controlsPanel));

  _controlsPanel.push_back(background);
  _controlsPanel.push_back(title);
  _controlsPanel.push_back(back);
  _controlsPanel.push_back(new KeyWidget(x / 8, y / 1.8f, y / 16.8, x / 30, FORWARD));
  _controlsPanel.push_back(new TextWidget(x / 8 + 2 * x / 30, y / 1.8f,
					  y / 16.8, x / 4, "Forward"));
  _controlsPanel.push_back(new KeyWidget(x / 8, y / 2.25f, y / 16.8, x / 30, BACK));
  _controlsPanel.push_back(new TextWidget(x / 8 + 2 * x / 30, y / 2.25f,
					  y / 16.8, x / 4, "Back"));
  _controlsPanel.push_back(new KeyWidget(x / 8, y / 3.0f, y / 16.8, x / 30, LEFT));
  _controlsPanel.push_back(new TextWidget(x / 8 + 2 * x / 30, y / 3.0f,
					  y / 16.8, x / 4, "Left"));
  _controlsPanel.push_back(new KeyWidget(x / 2 + x / 8, y / 1.8f,
					 y / 16.8, x / 30, RIGHT));
  _controlsPanel.push_back(new TextWidget(x / 2 + x / 8 + 2 * x / 30, y / 1.8f,
					  y / 16.8, x / 4, "Right"));
  _controlsPanel.push_back(new KeyWidget(x / 2 + x / 8, y / 2.25f,
					 y / 16.8, x / 30, DROPBOMB));
  _controlsPanel.push_back(new TextWidget(x / 2 + x / 8 + 2 * x / 30, y / 2.25f,
					  y / 16.8, x / 4, "DropBomb"));
  return (true);
}

bool		Menu::update()
{
  double	time;
  double	fps = (1000 / _gameInfo.set->getVar(FPS));
  int y = _gameInfo.set->getVar(W_HEIGHT);
  t_window	win;
  t_mouse	mouse;

  _gameInfo.input->getInput(*(_gameInfo.set));
  (*(_gameInfo.input))[mouse];
  (*_gameInfo.input)[win];
  if (mouse.event == BUTTONUP)
    for (std::vector<AWidget *>::iterator it = (*_currentPanel).begin(),
	   endit = (*_currentPanel).end(); it != endit ; ++it)
      if ((*it)->isClicked(mouse.x, y - mouse.y))
	{
	  (*it)->onClick(_gameInfo, (*this));
	  break;
	}
  _win.updateClock(*(_gameInfo.clock));
  if ((*(_gameInfo.input))[LAUNCHGAME])
    {
      launchGame();
      _gameInfo.sound->play("menu", MUSIC);
    }
  if (_gameInfo.input->isPressed(SDLK_F1))
    {
      glDisable(GL_DEPTH_TEST);
      _console->aff(_win, 1600.0f, 900.0f);
      glEnable(GL_DEPTH_TEST);
    }
  if (_gameInfo.input->isPressed(SDLK_ESCAPE) || win.event == WIN_QUIT)
    return (false);
  _frames++;
  if ((time = _gameInfo.clock->getElapsed()) < fps)
    {
      _frames = 0;
      usleep((fps - time) * 1000);
    }
  return (true);
}

void	Menu::draw()
{
  float x = _gameInfo.set->getVar(W_WIDTH), y = _gameInfo.set->getVar(W_HEIGHT);

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glViewport(0, 0, x, y);
  glDisable(GL_DEPTH_TEST);
  _textShader.bind();
  _textShader.setUniform("projection", glm::ortho(0.0f, x, 0.0f, y, -1.0f, 1.0f));
  _textShader.setUniform("view", glm::mat4(1));
  _textShader.setUniform("winX", x);
  _textShader.setUniform("winY", y);
  for (std::vector<AWidget *>::iterator it = (*_currentPanel).begin(),
	 endit = (*_currentPanel).end(); it != endit ; ++it)
    {
      (*it)->onDisplay(_filename, _filePos);
      (*it)->draw(_textShader, *_gameInfo.clock);
    }
  glEnable(GL_DEPTH_TEST);
  _win.flush();
}

void	Menu::handleClock(int &frame, double &time, double fps)
{
  time = _gameInfo.clock->getElapsed();
  if (time < fps)
    usleep((fps - time) * 1000);
  frame = (frame >= 100) ? 100 : frame + 1;
  _win.updateClock(*_gameInfo.clock);
}

bool	Menu::textFillBuf(std::string &buf, unsigned int maxlen, Keycode key)
{
  if (key >= SDLK_KP_0 && key <= SDLK_KP_9)
    key = '0' + key - SDLK_KP_0;
  if (key == '\r' || key == SDLK_KP_ENTER || key == 27)
    {
      buf.erase(buf.end() - 1);
      return (false);
    }
  else if (key > 0 && key < 128)
    {
      if (key == '\b' && buf.length() > 1)
	{
	  buf = buf.substr(0, buf.length() - 2);
	  buf.push_back('|');
	}
      else if (buf.length() < maxlen && key >= ' ' && key <= '~')
	{
	  buf.at(buf.length() - 1) = static_cast<char>(key);
	  buf.push_back('|');
	}
    }
  return (true);
}

void	Menu::textInput(std::string &buf, unsigned int maxlen)
{
  double	fps = 1000.0 / 25.0;
  double	time = 0;
  int		frame = -1;
  Keycode	key = 0;
  Keycode	save = -1;
  Input		*input = _gameInfo.input;

  buf.clear();
  buf.push_back('|');
  while (key != 27)
    {
      input->getInput(*(_gameInfo.set));
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      l_Keycit beg = input->getPressedBeg();
      l_Keycit end = input->getPressedEnd();
      if (beg != end && *beg == SDLK_LSHIFT)
	++beg;
      if (beg != end)
	{
	  key = *beg;
	  if (key >= SDLK_KP_1 && key <= SDLK_KP_0)
	    key = '0' + key - SDLK_KP_1 + 1;
	  if (save == key)
	    {
	      if (((key < 128 && key != '\b') && frame < 8) ||
		  (key == '\b' && frame < 2) ||
		  ((key == '\r' || key == SDLK_KP_ENTER) && frame < 15))
		{
		  handleClock(frame, time, fps);
		  continue;
		}
	      else
		frame = 0;
	    }
	  else
	    frame = 0;
	  save = key;
	}
      for (; beg != end; ++beg)
	if (textFillBuf(buf, maxlen, key) == false)
	  return ;
      handleClock(frame, time, fps);
      draw();
    }
}

void	Menu::launchGame()
{
  Map map(*(_gameInfo.set));
  _gameInfo.map = &map;
  GameEngine eng(&_win, &_textShader, &_gameInfo, true);
  bool	done = true;

  if (!eng.initialize())
    return ;
  while ((done = eng.update()))
    eng.draw();
  _gameInfo.map = NULL;
}

void	Menu::launch()
{
  if (!initialize())
    return ;
  while (!_done)
    {
      if (update() == false)
	return ;
      draw();
    }
  _win.stop();
}

void	Menu::setCurrentPanel(std::vector<AWidget *> *currentPanel)
{
  _currentPanel = currentPanel;
  _filePos = 0;
  if (_currentPanel == &_importMapPanel)
    readDir(MAPS_PATH);
  else if (_currentPanel == &_loadGamePanel)
    readDir(GAMES_PATH);
}

void	Menu::loadScore()
{
  std::ifstream file(SCORE_PATH);

  if (file)
    {
      std::string line;

      while (getline(file, line))
	{
	  std::stringstream ss(line);
	  std::string name;
	  int score;

	  ss >> name >> score;
	  if (name != "")
	    _gameInfo.score[name] = score;
	}
    }
}

void	Menu::saveScore()
{
  std::ofstream file(SCORE_PATH, std::ios::out | std::ios::trunc);

  for (std::map<std::string, int>::const_iterator it = _gameInfo.score.begin();it != _gameInfo.score.end();it++)
    file << it->first << " " << it->second << std::endl;
}

void	Menu::readDir(const std::string &dirname)
{
  DIR	*dirp;
  struct dirent *file;

  _filename.clear();
  if ((dirp = opendir(dirname.c_str())) == NULL)
    return ;
  while ((file = readdir(dirp)) != NULL)
    {
      if (file->d_type != DT_DIR)
	_filename.push_back(file->d_name);
    }
}

Menu	&Menu::operator++()
{
  if (_filename.size() > (_filePos + 1) * 4)
    ++_filePos;
  return (*this);
}

Menu	&Menu::operator--()
{
  if (_filePos > 0)
    --_filePos;
  return (*this);
}

void	Menu::setDone(bool done)
{
  _done = done;
}
