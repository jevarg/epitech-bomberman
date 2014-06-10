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
}

Menu::~Menu()
{
}

bool  Menu::initialize()
{
  int x = _gameInfo.set->getVar(W_WIDTH), y = _gameInfo.set->getVar(W_HEIGHT);
  
  if (!_win.start(_gameInfo.set->getVar(W_WIDTH), _gameInfo.set->getVar(W_HEIGHT), "Bomberman"))
    throw(Exception("Cannot open window"));
  glEnable(GL_DEPTH_TEST);
  if (!_textShader.load("./Shaders/text.fp", GL_FRAGMENT_SHADER) ||
      !_textShader.load("./Shaders/text.vp", GL_VERTEX_SHADER) ||
      !_textShader.build())
    return (false);
  _mainPanel.push_back(new NavigationWidget(x / 4, 520, y / 11.25f, x / 2, "./assets/singleplayer.tga", &_newGamePanel));
  _mainPanel.push_back(new NavigationWidget(x / 4, 400, y / 11.25f, x / 2, "./assets/multiplayers.tga", &_newGamePanel));
  _mainPanel.push_back(new NavigationWidget(x / 4, 280, y / 11.25f, x / 2, "./assets/option.tga", &_newGamePanel));
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
  if ((*(_gameInfo.input))[SDLK_ESCAPE]) // || _gameInfo.input->getInput(SDL_QUIT))
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
  // draw Widget here (need a draw function first, or may be Square need it)
  _textShader.bind();
  _textShader.setUniform("projection", glm::ortho(0.0f, x, 0.0f, y, -1.0f, 1.0f));
  _textShader.setUniform("view", glm::mat4(1));
  _textShader.setUniform("winX", x);
  _textShader.setUniform("winY", y);
  for (int i = 0; i < 3; ++i)
    (*_currentPanel)[i]->draw(_textShader, *_gameInfo.clock);
  glEnable(GL_DEPTH_TEST);
  _win.flush();
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
