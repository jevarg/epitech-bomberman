#include <iostream>
#include <cmath>
#include "GameEngine.hpp"

GameEngine::GameEngine(gdl::SdlContext *win, gdl::Clock *clock,
		       gdl::BasicShader *textShader, Map *map, Settings *set,
		       Input *input, Sound *sound)
  : _win(win), _textShader(textShader), _save(),
    _gameInfo(clock, map, set, input, sound), _lights(), _players()
{
  _gameInfo.mutex = new Mutex;
  _gameInfo.condvar = new Condvar;
  _shutdown = false;

  Mutex *mutex = _gameInfo.mutex;
  pthread_mutex_t * m = _gameInfo.mutex->getMutexPtr();
  _frames = 0;
  std::cout << &_gameInfo << " " << mutex
	    << " " << m
	    << " " << _gameInfo.condvar << std::endl;
}

GameEngine::~GameEngine()
{
  _player1->setDestroyAttr();
  _player2->setDestroyAttr();
  usleep(1000);
}

bool GameEngine::initialize()
{
  ModelFactory &fact = ModelFactory::getInstance();
  EntityFactory *ent = EntityFactory::getInstance();
  Spawn	spawn(_gameInfo.map);

  // _gameInfo.map->determineMapSize("map", x, y);
  _mapX = _gameInfo.set->getVar(MAP_HEIGHT);
  _mapY = _gameInfo.set->getVar(MAP_HEIGHT);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  if (!_shader.load("./Shaders/basic.fp", GL_FRAGMENT_SHADER)
      || !_shader.load("./Shaders/basic.vp", GL_VERTEX_SHADER)
      || !_shader.build())
    return (false);

  _gameInfo.sound->play("game", MUSIC);

  _hud = new HUD(*(_textShader));

  _ground = new Cube(WALL_TEXTURE);
  _ground->initialize();
  // _ground->translate(glm::vec3((((float)(_mapX) - 1.0) / 2.0),
  // 			      -1, (((float)(_mapY) - 1.0) / 2.0)));
  // _ground->scale(glm::vec3(_gameInfo.set->getVar(R_DEPTHVIEW) * 2,
  // 			   1.0,
  // 			   _gameInfo.set->getVar(R_DEPTHVIEW) * 2));

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

  _gameInfo.map->createMap(_gameInfo);
  // _gameInfo.map->load("map", _gameInfo);
  // spawn.setSpawnSize(_gameInfo.map->getWidth(), _gameInfo.map->getHeight());

  _player1 = new Player(0, 0, &_gameInfo, CHARACTER1, false);
  _player2 = new Player(0, 0, &_gameInfo, CHARACTER2, false);

  ent->addEntity(WALL, new Entity(0, 0, WALL, &_gameInfo));
  ent->addEntity(BOX, new Box(0, 0, &_gameInfo));
  ent->addEntity(BOMB, new Bomb(0, 0, NULL, &_gameInfo, false));
  ent->addEntity(FLAME, new Flame(0, 0, 1, 0, NORTH, &_gameInfo, NULL, false));
  ent->addEntity(CHARACTER1, _player1);
  ent->addEntity(CHARACTER2, _player2);
  ent->addEntity(BOT, new IA(0, 0, &_gameInfo, false));
  ent->addEntity(SPEEDITEM, new SpeedItem(0, 0, &_gameInfo, false));
  ent->addEntity(HEALTHITEM, new HealthItem(0, 0, &_gameInfo, false));
  ent->addEntity(STOCKITEM, new StockItem(0, 0, &_gameInfo, false));
  ent->addEntity(RANGEITEM, new RangeItem(0, 0, &_gameInfo, false));

  // spawn.spawnEnt(1, 0, _gameInfo);
  _players.push_back(_player1);
  // _players.push_back(_player2);
  spawn.spawnEnt(1, 0, _gameInfo);
  return (true);
}

void	GameEngine::mainInput()
{
  t_window	win;

  _gameInfo.input->getInput(*(_gameInfo.set));
  if (((*_gameInfo.input)[win] && win.event == WIN_QUIT) ||
      _gameInfo.input->isPressed(SDLK_ESCAPE))
    {
      _shutdown = true;
      v_Contcit end = _gameInfo.map->ContEnd();
      for (v_Contcit it = _gameInfo.map->ContBegin();it != end;it++)
	{
	  AEntity *ent;
	  v_Entit its;
	  l_Entit itm;
	  while ((ent = (*it)->listFront()) != NULL)
	    ent->setDestroy();
	  while ((ent = (*it)->vecFront()) != NULL)
	    ent->setDestroy();
	}
      return ;
    }
}

int		GameEngine::clearElements()
{
  return (_gameInfo.map->clearElements());
}

bool		GameEngine::update()
{
  double	time;
  double	fps = (1000 / _gameInfo.set->getVar(FPS));
  // static int	frame = 0;
  static double	elapsedTime = 0;
  t_mouse mouse;

  mainInput();
  (*_gameInfo.input)[mouse];
  std::cout << "event: " << mouse.event << std::endl;
  _gameInfo.condvar->broadcast();
  if (clearElements() == 0 && _shutdown)
    return (false);
  _frames++;
  time = _gameInfo.clock->getElapsed();
  elapsedTime += time;
  if (elapsedTime > 0.1)
    {
      _hud->setFps(round(_frames / elapsedTime));
      _frames = 0;
      elapsedTime = 0;
    }
  // ++frame;
  // if (frame == 600)
  //   {
  //     if (_save.saveGame(*(_gameInfo.map), *(_gameInfo.set), "save") == false)
  // 	std::cout << "failed to save game" << std::endl;
  //     else
  // 	std::cout << "game saved" << std::endl;
  //   }
  // if (frame > 600 && frame % 600 == 0)
  //   {
  //     if (_save.loadGame(*(_gameInfo.map), *(_gameInfo.set), "save", _gameInfo) == false)
  // 	std::cout << "failed to load game" << std::endl;
  //     else
  // 	std::cout << "loaded game successfully" << std::endl;
  //   }

  if (time < fps)
    usleep((fps - time) * 1000);
  _win->updateClock(*_gameInfo.clock);
  return (true);
}

void GameEngine::draw()
{
  int i = 0;
  int winX = _gameInfo.set->getVar(W_WIDTH), winY = _gameInfo.set->getVar(W_HEIGHT);

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  for (std::vector<Player *>::const_iterator player = _players.begin();player != _players.end();++player)
    {
      glViewport (i * (winX / _players.size()), 0, (winX / _players.size()), winY);
      ++i;

      int x = (*player)->getXPos(), y = (*player)->getYPos(), mapx = _mapX, mapy = _mapY;
      Camera &cam = (*player)->getCam();
      int depth_view = _gameInfo.set->getVar(R_DEPTHVIEW);
      float groundX = x, groundY = y, sizeX = depth_view * 2, sizeY = depth_view * 2;
      const std::vector<Container *>	&cont = _gameInfo.map->getCont();

      cam.lookAt();
      _shader.bind();
      _shader.setUniform("projection", cam.getProjection());
      _shader.setUniform("view", cam.getTransformation());
      _shader.setUniform("nbLight", static_cast<int>(_lights.size()));
      for (std::vector<Light *>::const_iterator it = _lights.begin();it != _lights.end();it++)
	(*it)->render(_shader);

      sizeY += 1;
      groundY += 0.5;
      if (groundX - depth_view < 0)
	{
	  sizeX -= ABS(groundX - depth_view);
	  groundX = sizeX / 2;
	}
      else if (groundX + depth_view > _gameInfo.map->getWidth())
	{
	  sizeX -= (groundX + depth_view - _gameInfo.map->getWidth());
	  groundX = _gameInfo.map->getWidth() - sizeX / 2;
	}
      if (groundY - depth_view < 0)
	{
	  sizeY -= ABS(groundY - depth_view);
	  groundY = sizeY / 2;
	}
      else if (groundY + depth_view > _gameInfo.map->getHeight())
	{
	  sizeY -= (groundY + depth_view - _gameInfo.map->getHeight());
	  groundY = _gameInfo.map->getHeight() - sizeY / 2;
	}
      groundX -= 0.5;
      groundY -= 0.5;
      _ground->setScale(glm::vec3(sizeX, 1.0, sizeY));
      _ground->setPos(glm::vec3(groundX, -1, groundY));
      _ground->draw(_shader, *_gameInfo.clock);
      for (int j = (y > depth_view) ? y - depth_view : 0;j <= y + depth_view && j < mapy;j++)
	for (int i = (x > depth_view) ? x - depth_view : 0;i < x + depth_view && i < mapx;i++)
	  {
	    std::vector<AEntity *> elem;
	    if (_gameInfo.map->checkFullMapColision(i, j, elem))
	      for (std::vector<AEntity *>::const_iterator it1 = elem.begin();
		   it1 != elem.end();it1++)
		{
		  if ((*it1)->getType() == WALL)
		    (*it1)->getModel()->setPos(glm::vec3(i, 0.0, j));
		  (*it1)->draw(_shader, *_gameInfo.clock);
		}
	  }
      _hud->draw(*player, _gameInfo);
      glFlush();
    }
  _win->flush();
}
