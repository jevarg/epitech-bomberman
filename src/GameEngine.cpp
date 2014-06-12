#include <iostream>
#include <cmath>
#include "GameEngine.hpp"

GameEngine::GameEngine(gdl::SdlContext *win, gdl::BasicShader *textShader, t_gameinfo *gameInfo,
		       bool multi)
  : _win(win), _textShader(textShader), _save(),
    _gameInfo(gameInfo), _lights(), _players(), _multi(multi)
{
  _player1 = NULL;
  _player2 = NULL;
  _gameInfo->mutex = new Mutex;
  _gameInfo->condvar = new Condvar;
  _shutdown = false;
  _frames = 0;
  _fps.initialize();
}

GameEngine::~GameEngine()
{
  if (_player1)
    _player1->setDestroyAttr();
  if (_player2)
    _player2->setDestroyAttr();
  delete _end_screen[0];
  delete _end_screen[1];
  _gameInfo->condvar->broadcast();
  sleep(1);
  delete _gameInfo->mutex;
  delete _gameInfo->condvar;
}

bool GameEngine::initialize()
{
  ModelFactory &fact = ModelFactory::getInstance();
  EntityFactory *ent = EntityFactory::getInstance();
  Spawn	spawn(_gameInfo->map);

  _end_screen[0] = new Square(WIN_TEXTURE);
  _end_screen[1] = new Square(LOSE_TEXTURE);

  if (!_end_screen[0]->initialize() || !_end_screen[1]->initialize())
    return (false);

  try
    {
      int x = 0, y = 0;
      _gameInfo->map->determineMapSize("map", x, y);
      _gameInfo->set->setVar(MAP_WIDTH, x);
      _gameInfo->set->setVar(MAP_HEIGHT, y);
      _mapX = _gameInfo->set->getVar(MAP_WIDTH);
      _mapY = _gameInfo->set->getVar(MAP_HEIGHT);
    }
  catch (Exception &e)
    {
      std::cerr << e.what() << std::endl;
      return (false);
    }

  glEnable(GL_DEPTH_TEST);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  if (!_shader.load("./Shaders/basic.fp", GL_FRAGMENT_SHADER)
      || !_shader.load("./Shaders/basic.vp", GL_VERTEX_SHADER)
      || !_shader.build())
    return (false);

  _end_screen[0]->setSize(420, 94);
  _end_screen[1]->setSize(490, 94);

  _end_screen[0]->setPos((800 / (_multi == true ? 2 : 1)) - 210, 450 - 47);
  _end_screen[1]->setPos((800 / (_multi == true ? 2 : 1)) - 245, 450 - 47);

  _end_screen[0]->fillGeometry();
  _end_screen[1]->fillGeometry();

  _gameInfo->sound->play("game", MUSIC);

  _hud = new HUD(*(_textShader));

  _ground = new Cube(WALL_TEXTURE);
  _ground->initialize();

  _skybox = new Cube(SKY_TEXTURE);
  _skybox->initialize();

  fact.addModel(WALL, new Cube(*_ground), WALL_TEXTURE);
  fact.addModel(BOX, new Cube(*_ground), BOX_TEXTURE);
  fact.addModel(FLAME, new Cube(*_ground), FLAME_TEXTURE);
  fact.addModel(SPEEDITEM, SPEEDITEM_MODEL);
  fact.addModel(HEALTHITEM, HEALTHITEM_MODEL);
  fact.addModel(STOCKITEM, STOCKITEM_MODEL);
  fact.addModel(RANGEITEM, RANGEITEM_MODEL);
  fact.addModel(CHARACTER1, CHARACTER_MODEL);
  fact.addModel(CHARACTER2, CHARACTER2_MODEL);
  fact.addModel(BOT, BOT_MODEL);
  fact.addModel(BOMB, BOMB_MODEL);

  _lights.push_back(new Light(_lights.size(), SUN, glm::vec3(1.0, 1.0, 1.0),
			      glm::vec3(_mapX / 2, 10, _mapY / 2), 1.0));

  _gameInfo->map->createMap(*_gameInfo);
  // _gameInfo->map->load("map", *_gameInfo);
   spawn.setSpawnSize(_gameInfo->map->getWidth(), _gameInfo->map->getHeight());

  _player1 = new Player(0, 0, _gameInfo, CHARACTER1, _multi);
  _player2 = new Player(0, 0, _gameInfo, CHARACTER2, _multi);

  ent->addEntity(WALL, new Entity(0, 0, WALL, _gameInfo));
  ent->addEntity(BOX, new Box(0, 0, _gameInfo));
  ent->addEntity(BOMB, new Bomb(0, 0, NULL, _gameInfo, false));
  ent->addEntity(FLAME, new Flame(0, 0, 1, 0, NORTH, _gameInfo, NULL, false));
  ent->addEntity(CHARACTER1, _player1);
  ent->addEntity(CHARACTER2, _player2);
  ent->addEntity(BOT, new IA(0, 0, _gameInfo, false));
  ent->addEntity(SPEEDITEM, new SpeedItem(0, 0, _gameInfo, false));
  ent->addEntity(HEALTHITEM, new HealthItem(0, 0, _gameInfo, false));
  ent->addEntity(STOCKITEM, new StockItem(0, 0, _gameInfo, false));
  ent->addEntity(RANGEITEM, new RangeItem(0, 0, _gameInfo, false));

  _players.push_back(_player1);
  if (_multi)
    _players.push_back(_player2);
  spawn.spawnEnt((_multi == true ? 2 : 1), 2, *_gameInfo);
  return (true);
}

void	GameEngine::mainInput()
{
  t_window	win;

  _gameInfo->input->getInput(*(_gameInfo->set));
  if (((*_gameInfo->input)[win] && win.event == WIN_QUIT) ||
      _gameInfo->input->isPressed(SDLK_ESCAPE))
    {
      _shutdown = true;
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
      return ;
    }
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
      _fps << (round(_frames / elapsedTime));
      _frames = 0;
      elapsedTime = 0;
    }
  // ++frame;
  // if (frame == 600)
  //   {
  //     if (_save.saveGame(*(_gameInfo->map), *(_gameInfo->set), "save") == false)
  // 	std::cout << "failed to save game" << std::endl;
  //     else
  // 	std::cout << "game saved" << std::endl;
  //   }
  // if (frame > 600 && frame % 600 == 0)
  //   {
  //     if (_save.loadGame(*(_gameInfo->map), *(_gameInfo->set), "save", _gameInfo) == false)
  // 	std::cout << "failed to load game" << std::endl;
  //     else
  // 	std::cout << "loaded game successfully" << std::endl;
  //   }

  if (time < fps)
    usleep((fps - time) * 1000);
  _win->updateClock(*_gameInfo->clock);
  return (true);
}

void GameEngine::draw()
{
  int i = 0;
  int winX = _gameInfo->set->getVar(W_WIDTH), winY = _gameInfo->set->getVar(W_HEIGHT);

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
      for (std::vector<Light *>::const_iterator it = _lights.begin();it != _lights.end();it++)
	(*it)->render(_shader);

      moveGround((*player));
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
		  (*it1)->draw(_shader, *_gameInfo->clock);
		}
	  }
      _hud->draw(*player, *_gameInfo, _multi);
      if ((*player)->getEnd() == WIN)
	_end_screen[0]->draw(*_textShader, *_gameInfo->clock);
      else if ((*player)->getEnd() == LOSE)
	_end_screen[1]->draw(*_textShader, *_gameInfo->clock);
    }
  if (_player1->getEnd() != 0 && _player2->getEnd() != 0)
    displayScore();
  _fps.draw(_shader, *_gameInfo->clock);
  _win->flush();
}

void	GameEngine::displayScore()
{
  float winX = _gameInfo->set->getVar(W_WIDTH), winY = _gameInfo->set->getVar(W_HEIGHT);
  Text score;
  int  i = 0;

  glViewport(0, 0, winX, winY);
  glDisable(GL_DEPTH_TEST);
  _textShader->bind();
  _textShader->setUniform("projection", glm::ortho(0.0f, winX, 0.0f, winY, -1.0f, 1.0f));
  _textShader->setUniform("view", glm::mat4(1));
  _textShader->setUniform("winX", winX);
  _textShader->setUniform("winY", winY);
  score.initialize();
  score.setText("Scores", 725, winY - 250, 50);
  score.draw(*_textShader, *_gameInfo->clock);
  for (std::map<std::string, int>::const_iterator it = _gameInfo->score.begin();it != _gameInfo->score.end();it++)
    {
      std::stringstream ss("");

      ss << it->first << " => " << it->second << " Point" << std::endl;
      score.setText(ss.str(), 650, winY - ((_gameInfo->score.size() - i) * 50 + 300),  40);
      score.draw(*_textShader, *_gameInfo->clock);
      ++i;
    }
  glEnable(GL_DEPTH_TEST);
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
