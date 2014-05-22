#include <iostream>
#include "GameEngine.hpp"

GameEngine::GameEngine(gdl::Clock &clock, Map &map, Settings &set, Input &input)
  : _save(), _gameInfo(clock, map, set, input)
{
  _gameInfo.mutex = new Mutex;
  _gameInfo.condvar = new Condvar;

  Mutex *mutex = _gameInfo.mutex;
  pthread_mutex_t * m = _gameInfo.mutex->getMutexPtr();
  std::cout << &_gameInfo << " " << mutex
	    << " " << m
	    << " " << _gameInfo.condvar << std::endl;
  getchar();
}


GameEngine::~GameEngine()
{
  // while (_obj.size())
  //   {
  //     delete _obj.back();
  //     _obj.pop_back();
  //   }
  _win.stop();
}

bool GameEngine::initialize()
{
  ModelFactory &fact = ModelFactory::getInstance();
  Cube *skybox;
  Spawn	spawn(_gameInfo.map);

  _mapX = _gameInfo.set.getVar(MAP_HEIGHT);
  _mapY = _gameInfo.set.getVar(MAP_WIDTH);
  if (!_win.start(_gameInfo.set.getVar(W_WIDTH),
		  _gameInfo.set.getVar(W_HEIGHT), "Bomberman"))
    throw(Exception("Cannot open window"));
  glEnable(GL_DEPTH_TEST);
  if (!_shader.load("./Shaders/basic.fp", GL_FRAGMENT_SHADER)
      || !_shader.load("./Shaders/basic.vp", GL_VERTEX_SHADER)
      || !_shader.build())
    return (false);
  _cam.translate(glm::vec3(0, 5, -10));

  skybox = new Cube(SKY_TEXTURE);
  skybox->initialize();
  skybox->scale(glm::vec3(200, 200, 200));
  _obj.push_back(skybox);

  skybox = new Cube(*skybox);
  skybox->translate(glm::vec3((((float)(_mapX) - 1.0) / 2.0),
			      -0.5, (((float)(_mapY) - 1.0) / 2.0)));
  skybox->scale(glm::vec3(_mapX, 0.0, _mapY));
  _obj.push_back(skybox);

  fact.addModel(WALL, new Cube(*skybox), WALL_TEXTURE);
  fact.addModel(BOX, new Cube(*skybox), BOX_TEXTURE);
  fact.addModel(CHARACTER, CHARACTER_MODEL);
  fact.addModel(BOMB, BOMB_MODEL);

  Camera *all_cam[1] = { &_cam };

  _gameInfo.map.createMap(_gameInfo);
  spawn.spawnEnt(1, 0, all_cam, _gameInfo);
  createDisplayBorder();
  return (true);
}

bool GameEngine::update()
{
  int	time;
  double	fps = (1000 / _gameInfo.set.getVar(FPS));
  t_mouse	mouse;
  t_window	win;

  _gameInfo.input.getInput(_gameInfo.set);
  _gameInfo.condvar->broadcast();
  if ((_gameInfo.input[win] && win.event == WIN_QUIT) || _gameInfo.input[SDLK_ESCAPE])
    {
      v_Contcit end = _gameInfo.map.ContEnd();
      for (v_Contcit it = _gameInfo.map.ContBegin();it != end;it++)
	{
	  l_Entit end_list = (*it)->listEndMod();
	  for (l_Entit it1 = (*it)->listBeginMod(); it1 != end_list; it1++)
	    (*it1)->setDestroy();
	}
      return (false);
    }
  if (_gameInfo.input[mouse])
    std::cout << "catched event " << mouse.event << std::endl;
  // if (win.event == WIN_RESIZE) // Seems not to work
  //   std::cout << "Resize to: " << win.x << " " << win.y << std::endl

  if ((time = _gameInfo.clock.getElapsed()) < fps)
    usleep((fps - time) * 1000);
  _win.updateClock(_gameInfo.clock);
  return (true);
}

void GameEngine::draw()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  _cam.lookAt();
  _shader.setUniform("model", glm::translate(glm::mat4(1.0f), _cam.getPosView()));
  _shader.setUniform("view", _cam.getTransformation());
  _shader.setUniform("projection", _cam.getProjection());
  _shader.bind();
  for (std::vector<IObject *>::const_iterator it = _obj.begin(); it != _obj.end(); it++)
    (*it)->draw(_shader, _gameInfo.clock);
  v_Contcit end = _gameInfo.map.ContEnd();
  for (v_Contcit it = _gameInfo.map.ContBegin();it != end;it++)
    {
      v_Entcit end_vector = (*it)->vecEnd();
      l_Entcit end_list = (*it)->listEnd();
      for (v_Entcit it1 = (*it)->vecBegin();it1 != end_vector;it1++)
	(*it1)->draw(_shader, _gameInfo.clock);
      for (l_Entcit it1 = (*it)->listBegin();it1 != end_list;it1++)
	(*it1)->draw(_shader, _gameInfo.clock);
    }
  _win.flush();
}

void GameEngine::createDisplayBorder()
{
  unsigned int	i;
  ModelFactory &fact = ModelFactory::getInstance();

  for (i = 0; i < _mapX; ++i)
    {
      _obj.push_back(fact.getModel(WALL));
      _obj.back()->translate(glm::vec3(i, 0.0, 0));
      _obj.push_back(fact.getModel(WALL));
      _obj.back()->translate(glm::vec3(i, 0.0, (_mapY - 1)));
    }
  for (i = 1; i < (_mapY - 1); ++i)
    {
      _obj.push_back(fact.getModel(WALL));
      _obj.back()->translate(glm::vec3((_mapX - 1), 0.0, i));
      _obj.push_back(fact.getModel(WALL));
      _obj.back()->translate(glm::vec3(0, 0.0, i));
    }
}
