#include <iostream>
#include <fstream>
#include <sstream>
#include "Menu.hpp"
#include "NavigationWidget.hpp"
#include "ImageWidget.hpp"
#include "InputWidget.hpp"

Menu::Menu(): _win(), _textShader(), _done(false), _gameInfo(NULL, NULL, NULL, NULL, NULL)
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
  ImageWidget	*background = new ImageWidget(0, 0, y, x, "./Ressources/Images/background.tga");
  ImageWidget	*title = new ImageWidget(x / 8, y / 1.43f, y / 4.8f, x / 1.3f, "./assets/BomberCraft.tga");
  NavigationWidget *back = new NavigationWidget(x / 8, y / 11.25f, y / 11.25f, x / 6.15f, "./assets/Button/back.tga", &_mainPanel);

  _mainPanel.push_back(background);
  _mainPanel.push_back(title);
  _mainPanel.push_back(new NavigationWidget(x / 4, y / 1.8f, y / 11.25f, x / 2, "./assets/Button/singleplayer.tga", &_newGamePanel));
  _mainPanel.push_back(new NavigationWidget(x / 4, y / 2.25f, y / 11.25f, x / 2, "./assets/Button/multiplayer.tga", &_newGamePanel));
  _mainPanel.push_back(new NavigationWidget(x / 4, y / 3.0f, y / 11.25f, x / 2, "./assets/Button/load_game.tga", &_loadGamePanel));
  _mainPanel.push_back(new NavigationWidget(x / 4, y / 4.5f, y / 11.25f, x / 2, "./assets/Button/options.tga", &_optionsPanel));
  _mainPanel.push_back(new ImageWidget(x / 4, y / 18, y / 11.25f, x / 2, "./assets/Button/quit.tga"));

  _mainPanel.push_back(new InputWidget(50, 50, y / 11.25f, x / 2, "allotest"));

  _newGamePanel.push_back(background);
  _newGamePanel.push_back(title);
  _newGamePanel.push_back(back);
  _newGamePanel.push_back(new ImageWidget(x / 4, 450, y / 11.25f, x / 2, "./assets/Button/generate_map.tga"));
  _newGamePanel.push_back(new NavigationWidget(x / 4, 300, y / 11.25f, x / 2, "./assets/Button/import_map.tga", &_importMapPanel));

  _loadGamePanel.push_back(background);
  _loadGamePanel.push_back(title);
  _loadGamePanel.push_back(back);
  // add input widget or input image
  _loadGamePanel.push_back(new ImageWidget(5.5f * (x / 8), y / 11.25f, y / 11.25f, x / 6.15f, "./assets/Button/load.tga"));

  _importMapPanel.push_back(background);
  _importMapPanel.push_back(title);
  _importMapPanel.push_back(back);
  // add input widget or input image
  _importMapPanel.push_back(new ImageWidget(5.5f * (x / 8), y / 11.25f, y / 11.25f, x / 6.15f, "./assets/Button/load.tga"));

  _optionsPanel.push_back(background);
  _optionsPanel.push_back(title);
  _optionsPanel.push_back(back);
  _optionsPanel.push_back(new ImageWidget(x / 4, y / 2.25f, y / 11.25f, x / 2, "./assets/Button/fullscreen_off.tga"));
  _optionsPanel.push_back(new NavigationWidget(x / 4, y / 3.0f, y / 11.25f, x / 2, "./assets/Button/controls.tga", &_controlsPanel));

  _controlsPanel.push_back(background);
  _controlsPanel.push_back(title);
  _controlsPanel.push_back(back);
  _controlsPanel.push_back(new ImageWidget(x / 4.5f, y / 1.8f, y / 11.25f, x / 6.15f, "./assets/Button/bind.tga"));
  _controlsPanel.push_back(new ImageWidget(x / 4.5f, y / 2.25f, y / 11.25f, x / 6.15f, "./assets/Button/bind.tga"));
  _controlsPanel.push_back(new ImageWidget(x / 4.5f, y / 3.0f, y / 11.25f, x / 6.15f, "./assets/Button/bind.tga"));
  _controlsPanel.push_back(new ImageWidget(x / 4.5f, y / 4.5f, y / 11.25f, x / 6.15f, "./assets/Button/bind.tga"));

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

void  Menu::draw()
{
  float x = _gameInfo.set->getVar(W_WIDTH), y = _gameInfo.set->getVar(W_HEIGHT);

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glDisable(GL_DEPTH_TEST);
  _textShader.bind();
  _textShader.setUniform("projection", glm::ortho(0.0f, x, 0.0f, y, -1.0f, 1.0f));
  _textShader.setUniform("view", glm::mat4(1));
  _textShader.setUniform("winX", x);
  _textShader.setUniform("winY", y);
  for (std::vector<AWidget *>::iterator it = (*_currentPanel).begin(),
	 endit = (*_currentPanel).end(); it != endit ; ++it)
    (*it)->draw(_textShader, *_gameInfo.clock);
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

void	Menu::textFillBuf(std::string &buf, unsigned int maxlen, Keycode key)
{
  if (key >= SDLK_KP_0 && key <= SDLK_KP_9)
    key = '0' + key - SDLK_KP_0;
  if (key == '\r' || key == SDLK_KP_ENTER)
    {
      buf.erase(buf.end() - 1);
      buf.clear();
      buf.push_back('|');
      return ;
    }
  else if (key > 0 && key < 128)
    {
      if (key == '\b' && buf.length() > 1)
	{
	  buf = buf.substr(0, buf.length() - 2);
	  buf.push_back('|');
	}
      else if (buf.length() < maxlen)
	{
	  buf.at(buf.length() - 1) = static_cast<char>(key);
	  buf.push_back('|');
	}
    }
}

void	Menu::textInput(std::string &buf, unsigned int maxlen, int x, int y)
{
  Text		text;
  double	fps = 1000.0 / 20.0;
  double	time = 0;
  int		frame = -1;
  Keycode	key = 0;
  Keycode	save = -1;
  Input		*input = _gameInfo.input;

  try
    {
      text.initialize();
    }
  catch (const Exception &e)
    {
      std::cerr << e.what() << std::endl;
      return ;
    }
  buf.clear();
  buf.push_back('|');
  while (key != 27)
    {
      input->getInput(*(_gameInfo.set));
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      l_Keycit beg = input->getPressedBeg();
      l_Keycit end = input->getPressedEnd();
      if (beg != end)
	{
	  save = *beg;
	  if (save == key && key < 128 && (isalpha(key) || key == ' ') &&
	      ((key == '\b' && frame < 2) ||
	       (key != '\b' && frame >= 0 && frame < 10)))
	    {
	      handleClock(frame, time, fps);
	      continue;
	    }
	  else
	    frame = 0;
	}
      for (; beg != end; ++beg)
	{
	  key = *beg;
	  textFillBuf(buf, maxlen, key);
	}
      handleClock(frame, time, fps);
      draw();
      text.setText(buf, x, y, POLICE_SIZE);
      glDisable(GL_DEPTH_TEST);
      text.draw(_textShader, *_gameInfo.clock);
      glEnable(GL_DEPTH_TEST);
      _win.flush();
    }
}

void	Menu::launchGame()
{
  Map map(*(_gameInfo.set));
  GameEngine eng(&_win, _gameInfo.clock, &_textShader, &map, _gameInfo.set,
		 _gameInfo.input, _gameInfo.sound);
  bool	done = true;

  if (!eng.initialize())
    return ;
  while ((done = eng.update()))
    eng.draw();
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

void	Menu::setDone(bool done)
{
  _done = done;
}
