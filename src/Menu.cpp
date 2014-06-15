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
#include "NameWidget.hpp"
#include "ResWidget.hpp"
#include "FullScreenWidget.hpp"
#include "ClickTextWidget.hpp"
#include "SaveWidget.hpp"
#include "SoundWidget.hpp"

Menu::Menu(): _win(), _textShader(), _done(false), _gameInfo(NULL, NULL, NULL, NULL, NULL, NULL),
	      _gameEngine(&_win, &_textShader, &_gameInfo)
{
  _frames = 0;
  _multi = false;
  _player1 = NULL;
  _player2 = NULL;
  _gameInfo.input = new Input();
  _gameInfo.set = new Settings();
  _gameInfo.sound = new Sound();
  _gameInfo.clock = new gdl::Clock();
  _gameInfo.map = NULL;
  _gameInfo.set->loadFile(DEFAULT_FILE);
  _gameInfo.set->loadFile(USER_FILE);
  loadScore();

  _currentPanel = &_mainPanel;
  _console = new Console(*_gameInfo.set, *_gameInfo.input, *_gameInfo.clock, _textShader);
  //    _console->aff(*_gameInfo.clock, _textShader, _win, *_gameInfo.input);
}

Menu::~Menu()
{
  AWidget	*background;
  AWidget	*title;
  AWidget	*back;

  background = *_newGamePanelSolo.begin();
  title = *(_newGamePanelSolo.begin() + 1);
  back = *(_newGamePanelSolo.begin() + 2);
  delete background;
  delete title;
  delete back;
  freePanel(background, title, back, _newGamePanelSolo);
  freePanel(background, title, back, _mainPanel);
  freePanel(background, title, back, _newGamePanelMulti);
  freePanel(background, title, back, _loadGamePanel);
  freePanel(background, title, back, _importMapPanel);
  freePanel(background, title, back, _optionsPanel);
  freePanel(background, title, back, _controlsPanel);
  freePanel(background, title, back, _screenPanel);
  freePanel(background, title, back, _pausePanel);
  saveScore();
}

void	Menu::freePanel(AWidget *background, AWidget *title,
			AWidget *back, std::vector<AWidget *> &panel)
{
  std::vector<AWidget *>::iterator	it;
  std::vector<AWidget *>::iterator	end;

  for (it = panel.begin(), end = panel.end(); it != end; ++it)
    {
      if (*it != back && *it != title && *it != background)
	delete (*it);
    }
}

bool  Menu::initialize()
{
  int x = _gameInfo.set->getVar(W_WIDTH), y = _gameInfo.set->getVar(W_HEIGHT);
  ModelFactory &fact = ModelFactory::getInstance();
  EntityFactory *ent = EntityFactory::getInstance();

  if (!_win.start(x, y, "Bomberman", SDL_INIT_EVERYTHING, SDL_WINDOW_OPENGL))
    throw(Exception("Cannot open window"));
  if (!_gameEngine.initialize())
    return (false);
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
					    "./assets/Button/singleplayer.tga", &_newGamePanelSolo));
  _mainPanel.push_back(new NavigationWidget(x / 4, y / 2.25f, y / 11.25f, x / 2,
					    "./assets/Button/multiplayer.tga", &_newGamePanelMulti));
  _mainPanel.push_back(new NavigationWidget(x / 4, y / 3.0f, y / 11.25f, x / 2,
					    "./assets/Button/load_game.tga", &_loadGamePanel));
  _mainPanel.push_back(new NavigationWidget(x / 4, y / 4.5f, y / 11.25f, x / 2,
					    "./assets/Button/options.tga", &_optionsPanel));
  _mainPanel.push_back(new QuitWidget(x / 4, y / 18, y / 11.25f, x / 2,
				      "./assets/Button/quit.tga"));

  _newGamePanelSolo.push_back(background);
  _newGamePanelSolo.push_back(title);
  _newGamePanelSolo.push_back(back);
  _newGamePanelSolo.push_back(new LaunchWidget(x / 4, y / 2.0f, y / 11.25f, x / 2,
					   "./assets/Button/generate_map.tga", &_mainPanel));
  _newGamePanelSolo.push_back(new NavigationWidget(x / 4, y / 2.5f, y / 11.25f, x / 2,
					       "./assets/Button/import_map.tga", &_importMapPanel));
  _newGamePanelSolo.push_back(new InputWidget(x - x / 5, y / 4.0, y / 11.25f, x / 8,
					      "./assets/input.tga", "Nb AI"));
  _newGamePanelSolo.push_back(new NameWidget(x / 4, y / 4.0, y / 11.25f, x / 2,
					     "./assets/input.tga", 1));

  _newGamePanelMulti.push_back(background);
  _newGamePanelMulti.push_back(title);
  _newGamePanelMulti.push_back(back);
  _newGamePanelMulti.push_back(new LaunchWidget(x / 4, y / 1.8f, y / 11.25f, x / 2,
					   "./assets/Button/generate_map.tga", &_mainPanel));
  _newGamePanelMulti.push_back(new NavigationWidget(x / 4, y / 2.25f, y / 11.25f, x / 2,
					       "./assets/Button/import_map.tga", &_importMapPanel));
  _newGamePanelMulti.push_back(new InputWidget(x - x / 5, y / 4.5, y / 11.25f, x / 8,
					      "./assets/input.tga", "Nb AI"));
  _newGamePanelMulti.push_back(new NameWidget(x / 4, y / 3.0, y / 11.25f, x / 2,
					       "./assets/input.tga", 1));
  _newGamePanelMulti.push_back(new NameWidget(x / 4, y / 4.5, y / 11.25f, x / 2,
					       "./assets/input.tga", 2));

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
  _optionsPanel.push_back(new FullScreenWidget(x / 4, y / 2.0f, y / 11.25f, x / 2,
					    "./assets/Button/button.tga", ""));
  _optionsPanel.push_back(new NavigationWidget(x / 4, y / 2.5f, y / 11.25f, x / 2,
					       "./assets/Button/controls.tga", &_controlsPanel));
  _optionsPanel.push_back(new SoundWidget(x / 4, y / 3.35f, y / 11.25f, x / 2,
					  "./assets/Button/button.tga", ""));
  // _optionsPanel.push_back(new NavigationWidget(x / 4, y / 3.35f, y / 11.25f, x / 2,
  // 					       "./assets/Button/resolution.tga", &_screenPanel));

  _controlsPanel.push_back(background);
  _controlsPanel.push_back(title);
  _controlsPanel.push_back(back);
  _controlsPanel.push_back(new KeyWidget(x / 8, y / 1.8f, y / 16.8, x / 30, FORWARD));
  _controlsPanel.push_back(new TextImgWidget(x / 8 + 2 * x / 30, y / 1.8f,
					     y / 16.8, x / 4,
					     "./assets/Button/button_small.tga", "Forward"));
  _controlsPanel.push_back(new KeyWidget(x / 8, y / 2.25f, y / 16.8, x / 30, BACK));
  _controlsPanel.push_back(new TextImgWidget(x / 8 + 2 * x / 30, y / 2.25f,
					  y / 16.8, x / 4,
					     "./assets/Button/button_small.tga", "Back"));
  _controlsPanel.push_back(new KeyWidget(x / 8, y / 3.0f, y / 16.8, x / 30, LEFT));
  _controlsPanel.push_back(new TextImgWidget(x / 8 + 2 * x / 30, y / 3.0f,
					  y / 16.8, x / 4,
					     "./assets/Button/button_small.tga", "Left"));
  _controlsPanel.push_back(new KeyWidget(x / 2 + x / 8, y / 1.8f,
					 y / 16.8, x / 30, RIGHT));
  _controlsPanel.push_back(new TextImgWidget(x / 2 + x / 8 + 2 * x / 30, y / 1.8f,
					  y / 16.8, x / 4,
					     "./assets/Button/button_small.tga", "Right"));
  _controlsPanel.push_back(new KeyWidget(x / 2 + x / 8, y / 2.25f,
					 y / 16.8, x / 30, DROPBOMB));
  _controlsPanel.push_back(new TextImgWidget(x / 2 + x / 8 + 2 * x / 30, y / 2.25f,
					  y / 16.8, x / 4,
					     "./assets/Button/button_small.tga", "Drop bomb"));

  _pausePanel.push_back(background);
  _pausePanel.push_back(title);
  _pausePanel.push_back(new ClickTextWidget(x / 4, y / 1.8f, y / 11.25f, x / 2,
				      "./assets/Button/button.tga", "Resume"));
  _pausePanel.push_back(new ClickTextWidget(x / 4, y / 2.25f, y / 11.25f, x / 2,
				      "./assets/Button/button.tga", "Save"));
  _pausePanel.push_back(new ClickTextWidget(x / 4, y / 3.0f, y / 11.25f, x / 2,
				      "./assets/Button/button.tga", "Quit"));


  _savePanel.push_back(background);
  _savePanel.push_back(title);
  _savePanel.push_back(new NavigationWidget(x / 8, y / 11.25f, y / 11.25f, x / 6.15f,
  					    "./assets/Button/back.tga", &_pausePanel));
  _savePanel.push_back(new TextImgWidget(x / 4, y / 2.25f, y / 11.25f, x / 2,
  				      "./assets/Button/button.tga", "Save your Game"));
  _savePanel.push_back(new SaveWidget(x / 4, y / 3.0f, y / 11.25f, x / 2,
  				      "./assets/input.tga", "Filename.map"));

  _screenPanel.push_back(background);
  _screenPanel.push_back(title);
  _screenPanel.push_back(back);
  _screenPanel.push_back(new ResWidget(x / 4, y / 1.8f, y / 11.25f, x / 2,
				      "./assets/Button/button.tga", "2880x1800"));
  _screenPanel.push_back(new ResWidget(x / 4, y / 2.25f, y / 11.25f, x / 2,
				      "./assets/Button/button.tga", "1920x1080"));
  _screenPanel.push_back(new ResWidget(x / 4, y / 3.0f, y / 11.25f, x / 2,
				      "./assets/Button/button.tga", "1280x1024"));
  _screenPanel.push_back(new ResWidget(x / 4, y / 4.5f, y / 11.25f, x / 2,
				      "./assets/Button/button.tga", "800x600"));

  _cube.initialize();
  fact.addModel(WALL, new Cube(_cube), WALL_TEXTURE);
  fact.addModel(BOX, new Cube(_cube), BOX_TEXTURE);
  fact.addModel(FLAME, new Cube(_cube), FLAME_TEXTURE);
  fact.addModel(SPEEDITEM, SPEEDITEM_MODEL);
  fact.addModel(HEALTHITEM, HEALTHITEM_MODEL);
  fact.addModel(STOCKITEM, STOCKITEM_MODEL);
  fact.addModel(RANGEITEM, RANGEITEM_MODEL);
  fact.addModel(CHARACTER1, CHARACTER_MODEL);
  fact.addModel(CHARACTER2, CHARACTER2_MODEL);
  fact.addModel(BOT, BOT_MODEL);
  fact.addModel(CHICKEN, _gameInfo.set->getVar(R_CRAZYCHICKEN) ? CRAZYCHICKEN_MODEL : CHICKEN_MODEL);
  fact.addModel(BOMB, BOMB_MODEL);

  _player1 = new Player(0, 0, &_gameInfo, CHARACTER1);
  _player2 = new Player(0, 0, &_gameInfo, CHARACTER2);

  ent->addEntity(WALL, new Entity(0, 0, WALL, &_gameInfo));
  ent->addEntity(BOX, new Box(0, 0, &_gameInfo));
  ent->addEntity(BOMB, new Bomb(0, 0, NULL, &_gameInfo, false));
  ent->addEntity(FLAME, new Flame(0, 0, 1, 0, NORTH, &_gameInfo, NULL, false));
  ent->addEntity(SPEEDITEM, new SpeedItem(0, 0, &_gameInfo, false));
  ent->addEntity(HEALTHITEM, new HealthItem(0, 0, &_gameInfo, false));
  ent->addEntity(STOCKITEM, new StockItem(0, 0, &_gameInfo, false));
  ent->addEntity(RANGEITEM, new RangeItem(0, 0, &_gameInfo, false));
  ent->addEntity(CHICKEN, new Chicken(0, 0, &_gameInfo, false));
  ent->addEntity(CHARACTER1, _player1);
  ent->addEntity(CHARACTER2, _player2);
  ent->addEntity(BOT, new IA(0, 0, &_gameInfo, false));

  _gameEngine.setPlayer(_player1, _player2);
  return (true);
}

bool		Menu::update()
{
  double	time;
  double	fps = (1000 / _gameInfo.set->getVar(FPS));
  int		y = _gameInfo.set->getVar(W_HEIGHT);
  t_window	win;
  t_mouse	mouse;

  _gameEngine.resetAlreadyPlayed();
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
  if (_gameInfo.input->isPressed(SDLK_F1))
    {
      glDisable(GL_DEPTH_TEST);
      _console->aff(_win, 1600.0f, 900.0f);
      glEnable(GL_DEPTH_TEST);
    }
  if ((_gameInfo.input->isPressed(SDLK_ESCAPE) && _currentPanel == &_mainPanel) ||
      win.event == WIN_QUIT)
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
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
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

void	Menu::setFullScreen(const Settings * const set)
{
  int	x;
  int	y;

  x = set->getVar(W_WIDTH);
  y = set->getVar(W_HEIGHT);
  _win.stop();
  if (!_win.start(x, y, "Bomberman", SDL_INIT_EVERYTHING, SDL_WINDOW_OPENGL | (set->getVar(R_FULLSCREEN) == 1 ? SDL_WINDOW_FULLSCREEN_DESKTOP : 0)))
    throw(Exception("Cannot open window"));
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

bool	Menu::textFillBuf(std::string &buf, unsigned int maxlen, Keycode key)
{
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

void	Menu::getPlayerName(std::string &name, int playerId) const
{
  int	count = 0;
  const std::vector<AWidget *> *panel;

  if (!_multi && playerId >= 2)
    playerId = 1;
  panel = (_multi ? &_newGamePanelMulti : &_newGamePanelSolo);
  for (std::vector<AWidget *>::const_iterator it = (*panel).begin(),
	 endit = (*panel).end(); it != endit ; ++it)
    {
      if (dynamic_cast<NameWidget *>(*it))
	{
	  ++count;
	  if (count == playerId)
	    {
	      name = (dynamic_cast<NameWidget *>(*it))->getContent();
	      break ;
	    }
	}
    }
}


int	Menu::getNbIa()
{
  const std::vector<AWidget *> *panel;
  int				res = 0;

  panel = (_multi ? &_newGamePanelMulti : &_newGamePanelSolo);
  for (std::vector<AWidget *>::const_iterator it = (*panel).begin(),
	 endit = (*panel).end(); it != endit ; ++it)
    {
      if (dynamic_cast<InputWidget *>(*it))
	{
	  std::string content((dynamic_cast<InputWidget *>(*it))->getContent());
	  std::stringstream ss(content);

	  ss >> res;
	  return (res);
	}
    }
  return (0);
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
	    key = '0' + (key == SDLK_KP_0 ? (key - 10) : key) - SDLK_KP_1 + 1;
	  else if (key == SDLK_KP_PERIOD)
	    key = '.';
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

int		Menu::pauseMenu()
{
  double	fps = (1000 / _gameInfo.set->getVar(FPS));
  int		y = _gameInfo.set->getVar(W_HEIGHT);
  double	time;
  t_window	win;
  t_mouse	mouse;
  std::string	content;

  if (_currentPanel == &_savePanel)
    return (update() == false ? 2 : 0);
    _gameInfo.input->getInput(*(_gameInfo.set));
  (*(_gameInfo.input))[mouse];
  (*_gameInfo.input)[win];
  if (_gameInfo.input->isPressed(SDLK_F1))
    {
      glDisable(GL_DEPTH_TEST);
      _console->aff(_win, 1600.0f, 900.0f);
      glEnable(GL_DEPTH_TEST);
    }
  if (win.event == WIN_QUIT)
    return (2);
  _frames++;
  draw();
  if (mouse.event == BUTTONUP)
    for (std::vector<AWidget *>::iterator it = (*_currentPanel).begin(),
	   endit = (*_currentPanel).end(); it != endit ; ++it)
      if ((*it)->isClicked(mouse.x, y - mouse.y))
	{
	  if (dynamic_cast<ClickTextWidget *>(*it))
	    {
	      content = dynamic_cast<ClickTextWidget *>(*it)->getContent();
	      if (content == "Resume")
		return (1);
	      else if (content == "Quit")
		return (2);
	      else
		{
		  setCurrentPanel(&_savePanel);
		  int	ret = 0;
		  while (_currentPanel == &_savePanel && ret == 0)
		    {
		      ret = (update() == false ? 2 : 0);
		      draw();
		    }
		  return (ret);
		}
	    }
	}
  if ((time = _gameInfo.clock->getElapsed()) < fps)
    {
      _frames = 0;
      usleep((fps - time) * 1000);
    }
  return (0);
}

void	Menu::launchGame(const std::string &file, int load)
{
  int	menuState;
  Map map(*(_gameInfo.set));
  _gameInfo.map = &map;
  bool	done = true;
  std::string name[2];

  getPlayerName(name[0], 1);
  getPlayerName(name[1], 2);
  _gameEngine.setShutdown(false);
  _gameEngine.setMulti(_multi);
  _gameEngine.setConsole(_console);
  _player1->setMulti(_multi);
  _player2->setMulti(_multi);
  _player1->setName(name[0]);
  _player2->setName(name[1]);
  if (load == 1)
    {
      if (!_gameEngine.loadSave(file))
	return ;
    }
  else if (load == 0)
    {
    if (!_gameEngine.loadMap(file, getNbIa()))
      return ;
    }
  while (1)
    {
      while ((done = _gameEngine.update()))
	_gameEngine.draw();
      if (_gameEngine.isShutedDown()) // Only when it has finished to shutdown
	{
	  setCurrentPanel(&_mainPanel);
	  break ;
	}
      setCurrentPanel(&_pausePanel);
      while ((menuState = pauseMenu()) == 0);
      if (menuState == 2)
	_gameEngine.setShutdown(true);
    }
  _gameInfo.map = NULL;
}

void	Menu::launch()
{
  Intro intro;

  if (!initialize())
      return ;
  if (intro.initialize("./Ressources/Video/intro.mp4"))
    intro.play(_gameInfo, _win, _textShader);
  while (!_done)
    {
      if (update() == false)
	return ;
      draw();
    }
  _win.stop();
}

void	Menu::setCurrentPanel(std::vector<AWidget *> * const currentPanel)
{
  _currentPanel = currentPanel;
  _filePos = 0;
  if (_currentPanel == &_importMapPanel)
	readDir(MAPS_PATH);
  else if (_currentPanel == &_loadGamePanel)
    readDir(GAMES_PATH);
  if (_currentPanel == &_newGamePanelSolo || _currentPanel == &_newGamePanelMulti)
    _multi = _currentPanel == &_newGamePanelMulti;
  for (std::vector<AWidget *>::iterator it = (*_currentPanel).begin(),
	 endit = (*_currentPanel).end(); it != endit ; ++it)
    (*it)->init(_gameInfo.set);
}

void	Menu::loadScore()
{
  std::ifstream file(SCORE_PATH);

  if (file)
    {
      std::string line;

      while (getline(file, line))
	{
	  for (std::string::iterator it = line.begin();it != line.end();++it)
	    (*it) ^= 25;
	  std::reverse(line.begin(), line.end());
	  std::stringstream ss(line);
	  std::string str_score;
	  std::string name;
	  int score;

	  ss >> str_score;
	  name = ss.str();
	  std::reverse(name.begin(), name.end());
	  std::reverse(str_score.begin(), str_score.end());
	  ss.clear();
	  ss.str(str_score);
	  ss >> score;
	  name = name.substr(0, name.find_last_of(' '));
	  if (name != "")
	    {
	      _gameInfo.score.name.push_back(name);
	      _gameInfo.score.score.push_back(score);
	    }
	}
    }
}

void	Menu::saveScore()
{
  std::ofstream file(SCORE_PATH, std::ios::out | std::ios::trunc);

  for (unsigned int i = 0;i < _gameInfo.score.score.size();++i)
    {
      std::stringstream ss("");

      ss << _gameInfo.score.name[i] << " " << _gameInfo.score.score[i];
      std::string line(ss.str());
      for (std::string::iterator it = line.begin();it != line.end();++it)
	(*it) ^= 25;
      file << line << std::endl;
    }
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
