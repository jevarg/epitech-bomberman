#include <iostream>
#include <cmath>
#include "GameEngine.hpp"

GameEngine::GameEngine(gdl::SdlContext *win, gdl::BasicShader *textShader, t_gameinfo *gameInfo)
  : _win(win), _shader(), _textShader(textShader),
    _gameInfo(gameInfo), _lights(), _players()
{
  _player1 = NULL;
  _player2 = NULL;
  _shutdown = false;
  _multi = false;
  _frames = 0;
  _ground = NULL;
  _skybox = NULL;
  _console = NULL;
  _already_played = false;
  _fps.initialize();
  _gameInfo->mutex = new Mutex;
  _gameInfo->condvar = new Condvar;
  _gameInfo->save = new Save;
  _end_screen[0] = new Square(WIN_TEXTURE);
  _end_screen[1] = new Square(LOSE_TEXTURE);
}

GameEngine::~GameEngine()
{
  delete _end_screen[0];
  delete _end_screen[1];

  if (_ground)
    delete _ground;
  if (_skybox)
    delete _skybox;
  if (_console)
    delete _console;
  _player1->setDestroyAttr();
  _player2->setDestroyAttr();
  _gameInfo->condvar->broadcast();
  sleep(1);
  delete _gameInfo->condvar;
  delete _gameInfo->save;
  delete _gameInfo->mutex;
}

bool GameEngine::initialize()
{
  if (!_end_screen[0]->initialize() || !_end_screen[1]->initialize())
    return (false);

  if (!_shader.load("./Shaders/basic.fp", GL_FRAGMENT_SHADER)
      || !_shader.load("./Shaders/basic.vp", GL_VERTEX_SHADER)
      || !_shader.build())
    return (false);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  _end_screen[0]->setSize(420, 94);
  _end_screen[1]->setSize(490, 94);

  _hud = new HUD(*(_textShader));

  _ground = new Cube(WALL_TEXTURE);
  _ground->initialize();

  _skybox = new Cube(SKY_TEXTURE);
  _skybox->initialize();
  _skybox->scale(glm::vec3(50.0, 50.0, 50.0));

  _fps.initialize();
  return (true);
}

void	GameEngine::mainInput()
{
  t_window	win;

  _gameInfo->input->getInput(*(_gameInfo->set));
  if (_gameInfo->input->isPressed(SDLK_F1))
    {
      glDisable(GL_DEPTH_TEST);
      _console->aff(*_win, _gameInfo->set->getVar(W_WIDTH), _gameInfo->set->getVar(W_HEIGHT));
      glEnable(GL_DEPTH_TEST);
    }
  if (((*_gameInfo->input)[win] && win.event == WIN_QUIT))
    setShutdown(true);
}

int		GameEngine::clearElements()
{
  return (_gameInfo->map->clearElements());
}

bool		GameEngine::update()
{
  double	time;
  double	fps = (1000 / _gameInfo->set->getVar(FPS));
  // static int	frame = 0;
  static double	elapsedTime = 0;
  t_mouse mouse;
  int nbPlayer = _gameInfo->map->nbPlayer();

  mainInput();
  if (_gameInfo->input->isPressed(SDLK_ESCAPE) && _shutdown == false)
    return (false);
  if (_player1->isAlive() && nbPlayer == 1)
    _player1->setEnd(WIN);
  if (_player2->isAlive() && nbPlayer == 1)
    _player2->setEnd(WIN);
  (*_gameInfo->input)[mouse];
  _gameInfo->condvar->broadcast();
  if (clearElements() == 0 && _shutdown)
    return (false);
  _frames++;
  time = _gameInfo->clock->getElapsed();
  elapsedTime += time;
  if (elapsedTime > 0.1)
    {
      std::stringstream ss("");
      ss << "FPS: " << (round(_frames / elapsedTime));
      _fps.setText(ss.str(), _gameInfo->set->getVar(W_WIDTH) - 200,
		   _gameInfo->set->getVar(W_HEIGHT) - 50, 50);
      _frames = 0;
      elapsedTime = 0;
    }
  if (time < fps)
    usleep((fps - time) * 1000);
  _win->updateClock(*_gameInfo->clock);
  return (true);
}

void GameEngine::draw()
{
  int i = 0;
  float winX = _gameInfo->set->getVar(W_WIDTH), winY = _gameInfo->set->getVar(W_HEIGHT);

  if (_shutdown)
    return ;

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  for (std::vector<Player *>::const_iterator player = _players.begin();player != _players.end();++player)
    {
      glViewport (i * (winX / _players.size()), 0, (winX / _players.size()), winY);
      ++i;

      unsigned int x = (*player)->getXPos(), y = (*player)->getYPos();
      unsigned int depth_view = _gameInfo->set->getVar(R_DEPTHVIEW);
      Camera &cam = (*player)->getCam();
      const std::vector<Container *>	&cont = _gameInfo->map->getCont();

      cam.lookAt();
      _shader.bind();
      _shader.setUniform("projection", cam.getProjection());
      _shader.setUniform("view", cam.getTransformation());
      _shader.setUniform("nbLight", static_cast<int>(_lights.size()));
      for (std::vector<Light *>::const_iterator it = _lights.begin();
	   it != _lights.end();it++)
	(*it)->render(_shader);

      moveGround((*player));
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
      _skybox->draw(_shader, *_gameInfo->clock);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
      _ground->draw(_shader, *_gameInfo->clock);
      for (unsigned int j = (y > depth_view) ? y - depth_view : 0;j <= y + depth_view && j < _mapY;j++)
	for (unsigned int i = (x > depth_view) ? x - depth_view : 0;i < x + depth_view && i < _mapX;i++)
	  {
	    std::vector<AEntity *> elem;
	    if (_gameInfo->map->checkFullMapColision(i, j, elem))
	      for (std::vector<AEntity *>::const_iterator it1 = elem.begin();
		   it1 != elem.end();it1++)
		{
		  if ((*it1)->getType() == WALL)
		    (*it1)->getModel()->setPos(glm::vec3(i, 0.0, j));
		  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		  (*it1)->draw(_shader, *_gameInfo->clock);
		}
	  }
      _hud->draw(*player, *_gameInfo, _multi);
      if ((*player)->getEnd() == WIN)
	{
	  _end_screen[0]->draw(*_textShader, *_gameInfo->clock);
	  if (_already_played == false)
	    {
	      _gameInfo->sound->play("endgame", EFFECT);
	      _already_played = true;
	    }
	}
      else if ((*player)->getEnd() == LOSE)
	{
	  _end_screen[1]->draw(*_textShader, *_gameInfo->clock);
	  if (_already_played == false)
	    {
	      _gameInfo->sound->play("endgame", EFFECT);
	      _already_played = true;
	    }
	}
    }
  glViewport(0, 0, winX, winY);
  glDisable(GL_DEPTH_TEST);
  _textShader->bind();
  _textShader->setUniform("projection", glm::ortho(0.0f, winX, 0.0f, winY, -1.0f, 1.0f));
  _textShader->setUniform("view", glm::mat4(1));
  _textShader->setUniform("winX", winX);
  _textShader->setUniform("winY", winY);
  if (_player1->getEnd() != 0 && _player2->getEnd() != 0)
    displayScore();
  _fps.draw(*_textShader, *_gameInfo->clock);
  glEnable(GL_DEPTH_TEST);
  _win->flush();
}

void	GameEngine::displayScore()
{
  float winX = _gameInfo->set->getVar(W_WIDTH), winY = _gameInfo->set->getVar(W_HEIGHT);
  Text score;
  int  i = 0;

  score.initialize();
  score.setText("Scores", (winX - 75) / 2, winY - 250, 50);
  score.draw(*_textShader, *_gameInfo->clock);
  for (std::map<std::string, int>::const_iterator it = _gameInfo->score.begin();it != _gameInfo->score.end();it++)
    {
      std::stringstream ss("");

      ss << it->first << " => " << it->second << " Point" << std::endl;
      score.setText(ss.str(), (winX / 2) - 150, winY - ((_gameInfo->score.size() - i) * 50 + 300), 40);
      score.draw(*_textShader, *_gameInfo->clock);
      ++i;
    }
}

void	GameEngine::moveGround(Player *player)
{
  int x = player->getXPos(), y = player->getYPos();
  int depth_view = _gameInfo->set->getVar(R_DEPTHVIEW);
  float groundX = x, groundY = y, sizeX = depth_view * 2, sizeY = depth_view * 2;

  sizeY += 1;
  groundY += 0.5;
  if (groundX - depth_view < 0)
    {
      sizeX -= ABS(groundX - depth_view);
      groundX = sizeX / 2;
    }
  else if (groundX + depth_view > _gameInfo->map->getWidth())
    {
      sizeX -= (groundX + depth_view - _gameInfo->map->getWidth());
      groundX = _gameInfo->map->getWidth() - sizeX / 2;
    }
  if (groundY - depth_view < 0)
    {
      sizeY -= ABS(groundY - depth_view);
      groundY = sizeY / 2;
    }
  else if (groundY + depth_view > _gameInfo->map->getHeight())
    {
      sizeY -= (groundY + depth_view - _gameInfo->map->getHeight());
      groundY = _gameInfo->map->getHeight() - sizeY / 2;
    }
  groundX -= 0.5;
  groundY -= 0.5;
  _ground->setScale(glm::vec3(sizeX, 1.0, sizeY));
  _ground->setPos(glm::vec3(groundX, -1, groundY));
}

void	GameEngine::setMulti(bool multi)
{
  _multi = multi;
}

void	GameEngine::setPlayer(Player *player1, Player *player2)
{
  _player1 = player1;
  _player2 = player2;
}

void	GameEngine::setShutdown(bool shutdown)
{
  _shutdown = shutdown;
  if (_shutdown == false)
    return ;
  v_Contcit end = _gameInfo->map->ContEnd();
  for (v_Contcit it = _gameInfo->map->ContBegin();it != end;it++)
    {
      AEntity *ent;
      v_Entit its;
      l_Entit itm;
      while ((ent = (*it)->listFront()) != NULL)
	ent->setDestroy();
      while ((ent = (*it)->vecFront()) != NULL)
	ent->setDestroy();
    }
  _gameInfo->condvar->broadcast();
}

void	GameEngine::setConsole(Console * const console)
{
  _console = console;
}

bool	GameEngine::isShutingDown() const
{
  return (_shutdown);
}

bool	GameEngine::loadSave(const std::string &file)
{
  _gameInfo->save->loadGame(file, *_gameInfo);
  _mapY = _gameInfo->set->getVar(MAP_HEIGHT);
  _mapX = _gameInfo->set->getVar(MAP_WIDTH);
  while (!_lights.empty())
    _lights.pop_back();
  while (!_players.empty())
    _players.pop_back();

  _lights.push_back(new Light(_lights.size(), SUN, glm::vec3(1.0, 1.0, 1.0),
			      glm::vec3(_mapX / 2, 10, _mapY / 2), 1.0));

  _players.push_back(_player1);
  if (_multi)
    _players.push_back(_player2);
  _gameInfo->sound->play("game", MUSIC);
  return (true);
}

bool	GameEngine::loadMap(const std::string &file, int ia)
{
  Spawn	spawn(_gameInfo->map);
  int	winX = _gameInfo->set->getVar(W_WIDTH), winY = _gameInfo->set->getVar(W_HEIGHT);

  if (file != "")
    {
      try
	{
	  int x = 0, y = 0;
	  _gameInfo->map->determineMapSize(file, x, y);
	  _gameInfo->map->load("map", *_gameInfo);
	  _mapX = x;
	  _mapY = y;
	}
      catch (const Exception &e)
	{
	  std::cerr << e.what() << std::endl;
	  return (false);
	}
    }
  else
    {
      _gameInfo->map->createMap(*_gameInfo);
      _mapX = _gameInfo->set->getVar(MAP_WIDTH);
      _mapY = _gameInfo->set->getVar(MAP_HEIGHT);
    }

  while (!_lights.empty())
    _lights.pop_back();
  while (!_players.empty())
    _players.pop_back();

  _lights.push_back(new Light(_lights.size(), SUN, glm::vec3(1.0, 1.0, 1.0),
			      glm::vec3(_mapX / 2, 10, _mapY / 2), 1.0));

  _gameInfo->sound->play("game", MUSIC);

  spawn.setSpawnSize(_gameInfo->map->getWidth(), _gameInfo->map->getHeight());

  _end_screen[0]->setPos(((winX / 2) / (_multi == true ? 2 : 1)) - 210, (winY / 2) - 47);
  _end_screen[1]->setPos(((winX / 2) / (_multi == true ? 2 : 1)) - 245, (winY / 2) - 47);

  _end_screen[0]->fillGeometry();
  _end_screen[1]->fillGeometry();

  _players.push_back(_player1);
  if (_multi)
    _players.push_back(_player2);
  ia = (ia == 0 && _multi == true) ? 0 : ((ia <= 0) ? 1 : ia);
  spawn.spawnEnt((_multi == true ? 2 : 1), ia, *_gameInfo);
  return (true);
}

void	GameEngine::resetAlreadyPlayed()
{
  _already_played = false;
}
