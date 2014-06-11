#include "Menu.hpp"
#include "NavigationWidget.hpp"

Menu::Menu(): _win(), _textShader(), _done(false), _gameInfo(NULL, NULL, NULL, NULL, NULL)
{
  _frames = 0;
  _gameInfo.input = new Input();
  _gameInfo.set = new Settings();
  _gameInfo.sound = new Sound();
  _gameInfo.clock = new gdl::Clock();
  _gameInfo.set->loadFile(DEFAULT_FILE);
  _gameInfo.set->loadFile(USER_FILE);
  _currentPanel = &_mainPanel;
  _console = new Console(*_gameInfo.set, *_gameInfo.input, *_gameInfo.clock, _textShader);
  //    _console->aff(*_gameInfo.clock, _textShader, _win, *_gameInfo.input);
}

Menu::~Menu()
{
}

bool  Menu::initialize()
{
  if (!_win.start(_gameInfo.set->getVar(W_WIDTH), _gameInfo.set->getVar(W_HEIGHT), "Bomberman"))
    throw(Exception("Cannot open window"));
  glEnable(GL_DEPTH_TEST);
  if (!_textShader.load("./Shaders/text.fp", GL_FRAGMENT_SHADER) ||
      !_textShader.load("./Shaders/text.vp", GL_VERTEX_SHADER) ||
      !_textShader.build())
    return (false);
  _mainPanel.push_back(new NavigationWidget(50, 50, 40, 400, "allo", &_loadPanel)); // tmp
  // fill Panels vectors with Widgets
  return (true);
}

bool  Menu::update()
{
  double time;
  double fps = (1000 / _gameInfo.set->getVar(FPS));

  _gameInfo.input->getInput(*(_gameInfo.set));
  _win.updateClock(*(_gameInfo.clock));
  if ((*(_gameInfo.input))[LAUNCHGAME])
    launchGame();
  if (_gameInfo.input->isPressed(SDLK_F1))
    {
      glDisable(GL_DEPTH_TEST);
      _console->aff(_win, 1600.0f, 900.0f);
      glEnable(GL_DEPTH_TEST);
    }
    // _console->aff(*_gameInfo.clock, _textShader, _win, *_gameInfo.input);
  if (_gameInfo.input->isPressed(SDLK_ESCAPE)) // || _gameInfo.input->getInput(SDL_QUIT))
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
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glDisable(GL_DEPTH_TEST);
  _textShader.bind();
  _textShader.setUniform("projection", glm::ortho(0.0f, 1600.0f, 900.0f, 0.0f, -1.0f, 1.0f));
  _textShader.setUniform("view", glm::mat4(1));
  // draw Widget here (need a draw function first, or may be Square need it)
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
      text.draw(_textShader, *_gameInfo.clock);
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
