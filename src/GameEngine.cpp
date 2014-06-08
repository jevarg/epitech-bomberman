#include <iostream>
#include <cmath>
#include "GameEngine.hpp"

GameEngine::GameEngine(gdl::SdlContext *win, gdl::Clock *clock,
		       gdl::BasicShader *textShader, Map *map, Settings *set,
		       Input *input, Sound *sound)
  : _win(win), _textShader(textShader), _save(),
    _gameInfo(clock, map, set, input, sound), _lights()
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
}

bool GameEngine::initialize()
{
  ModelFactory &fact = ModelFactory::getInstance();
  EntityFactory *ent = EntityFactory::getInstance();
  Spawn	spawn(_gameInfo.map);

  // _gameInfo.map->determineMapSize("bigmap", x, y);
  // _gameInfo.set->setVar(MAP_WIDTH, x);
  // _gameInfo.set->setVar(MAP_HEIGHT, y);
  _mapX = _gameInfo.set->getVar(MAP_HEIGHT);
  _mapY = _gameInfo.set->getVar(MAP_WIDTH);

  glEnable(GL_DEPTH_TEST);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  if (!_shader.load("./Shaders/basic.fp", GL_FRAGMENT_SHADER)
      || !_shader.load("./Shaders/basic.vp", GL_VERTEX_SHADER)
      || !_shader.build())
    return (false);

  _hud = new HUD(_textShader);

  _ground = new Cube(WALL_TEXTURE);
  _ground->initialize();
  // _ground->translate(glm::vec3((((float)(_mapX) - 1.0) / 2.0),
  // 			      -0.5, (((float)(_mapY) - 1.0) / 2.0)));
  _ground->scale(glm::vec3(((_mapX < 10) ? _mapX : 10), 1, ((_mapY < 10) ? _mapY : 10)));

  fact.addModel(WALL, new Cube(*_ground), WALL_TEXTURE);
  fact.addModel(BOX, new Cube(*_ground), BOX_TEXTURE);
  fact.addModel(FLAME, new Cube(*_ground), FLAME_TEXTURE);
  fact.addModel(SPEEDITEM, SPEEDITEM_MODEL);
  fact.addModel(HEALTHITEM, HEALTHITEM_MODEL);
  fact.addModel(STOCKITEM, SPEEDITEM_MODEL);
  fact.addModel(RANGEITEM, SPEEDITEM_MODEL);
  fact.addModel(CHARACTER1, CHARACTER_MODEL);
  fact.addModel(CHARACTER2, CHARACTER_MODEL);
  fact.addModel(BOT, CHARACTER_MODEL);
  fact.addModel(BOMB, BOMB_MODEL);

  _lights.push_back(new Light(_lights.size(), SUN, glm::vec3(1.0, 1.0, 1.0),
			      glm::vec3(_mapX / 2, 10, _mapY / 2), 1.0));

  _gameInfo.map->createMap(_gameInfo);
  // _gameInfo.map->load("bigmap", _gameInfo);
  // spawn.setSpawnSize(_gameInfo.map->getWidth(), _gameInfo.map->getHeight());

  _player1 = new Player(0, 0, &_gameInfo, CHARACTER1);
  _player2 = new Player(0, 0, &_gameInfo, CHARACTER2);

  ent->addEntity(WALL, new Entity(0, 0, WALL, &_gameInfo));
  ent->addEntity(BOX, new Box(0, 0, &_gameInfo));
  ent->addEntity(BOMB, new Bomb(0, 0, NULL, &_gameInfo, false));
  ent->addEntity(FLAME, new Flame(0, 0, 1, 0, NORTH, &_gameInfo, false));
  ent->addEntity(CHARACTER1, _player1);
  ent->addEntity(CHARACTER2, _player2);
  ent->addEntity(BOT, new IA(0, 0, &_gameInfo, false));
  ent->addEntity(SPEEDITEM, new SpeedItem(0, 0, &_gameInfo, false));
  ent->addEntity(HEALTHITEM, new HealthItem(0, 0, &_gameInfo, false));
  ent->addEntity(STOCKITEM, new StockItem(0, 0, &_gameInfo, false));
  ent->addEntity(RANGEITEM, new RangeItem(0, 0, &_gameInfo, false));

  spawn.spawnEnt(1, 0, _gameInfo);
  return (true);
}

void	GameEngine::mainInput()
{
  t_window	win;

  _gameInfo.input->getInput(*(_gameInfo.set));
  if (((*_gameInfo.input)[win] && win.event == WIN_QUIT) ||
      (*_gameInfo.input)[SDLK_ESCAPE])
    {
      _shutdown = true;
      v_Contcit end = _gameInfo.map->ContEnd();
      for (v_Contcit it = _gameInfo.map->ContBegin();it != end;it++)
	{
	  AEntity *ent;
	  v_Entit its;
	  l_Entit itm;
	  /*	  while ((ent = (*it)->listFront()) != NULL)
	    ent->setDestroy();
	  while ((ent = (*it)->vecFront()) != NULL)
	    ent->setDestroy();
	  */}
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
  static double	elapsedTime = 0;

  mainInput();
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
  if (time < fps)
    usleep((fps - time) * 1000);
  _win->updateClock(*_gameInfo.clock);
  return (true);
}

void GameEngine::draw()
{
  int x = _player1->getXPos(), y = _player1->getYPos(), mapx = _mapX, mapy = _mapY;
  Camera &cam = _player1->getCam();
  const std::vector<Container *>	&cont = _gameInfo.map->getCont();

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  cam.lookAt();
  _shader.bind();
  _shader.setUniform("projection", cam.getProjection());
  _shader.setUniform("view", cam.getTransformation());
  _shader.setUniform("nbLight", static_cast<int>(_lights.size()));

  for (std::vector<Light *>::const_iterator it = _lights.begin();it != _lights.end();it++)
    (*it)->render(_shader);

  float groundX = x - 0.5, groundY = y - 0.5;
  // float posX = x - 0.5, posY = y - 0.5;

  if (x + 5 >= mapx)
    groundX -= (x + 5 - mapx);
  else if (x - 5 <= 0)
    groundX += (-(x - 5));

  if (y + 5 >= mapy)
    groundY -= (y + 5 - mapy);
  else if (y - 5 <= 0)
    groundY += (-(y - 5));

  _ground->setScale(glm::vec3((x + 5) < 10 ? x  + 5 : 10, 1.0, (y + 5) < 10 ? y + 5 : 10));
  _ground->setPos(glm::vec3(groundX, -1, groundY));
  _ground->draw(_shader, *_gameInfo.clock);

  for (int j = (y > 5) ? y - 5 : 0;j <= y + 5 && j < mapy;j++)
    for (int i = (x > 5) ? x - 5 : 0;i < x + 5 && i < mapx;i++)
      {
	AEntity *tmp = _gameInfo.map->getEntity(i, j);
	if (tmp != NULL)
	  {
	    if (tmp->getType() == WALL)
	      tmp->getModel()->setPos(glm::vec3(i, 0.0, j));
	    tmp->draw(_shader, *_gameInfo.clock);
	  }
      }
  _hud->draw(_player1, _gameInfo);
  _win->flush();
}
