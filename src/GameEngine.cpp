#include <iostream>
#include <cmath>
#include "GameEngine.hpp"

GameEngine::GameEngine(gdl::SdlContext *win, gdl::Clock &clock,
		       gdl::BasicShader *textShader, Map &map, Settings &set, Input &input)
  : _win(win), _textShader(textShader), _save(), _text(), _gameInfo(clock, map, set, input)
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
  // while (_obj.size())
  //   {
  //     delete _obj.back();
  //     _obj.pop_back();
  //   }
  _win->stop();
}

bool GameEngine::initialize()
{
  ModelFactory &fact = ModelFactory::getInstance();
  ItemFactory *items = ItemFactory::getInstance();
  Cube *skybox;
  Spawn	spawn(_gameInfo.map);

  _mapX = _gameInfo.set.getVar(MAP_HEIGHT);
  _mapY = _gameInfo.set.getVar(MAP_WIDTH);
  if (!_shader.load("./Shaders/text.fp", GL_FRAGMENT_SHADER)
      || !_shader.load("./Shaders/text.vp", GL_VERTEX_SHADER)
      || !_shader.build())
    return (false);
  _cam.translate(glm::vec3(0, 5, 10));

  if (!_text.initialize())
    return (false);

  skybox = new Cube(WALL_TEXTURE);
  skybox->initialize();
  skybox->translate(glm::vec3((((float)(_mapX) - 1.0) / 2.0),
			      -0.5, (((float)(_mapY) - 1.0) / 2.0)));
  skybox->scale(glm::vec3(_mapX, 0.0, _mapY));
  _obj.push_back(skybox);

  fact.addModel(WALL, new Cube(*skybox), WALL_TEXTURE);
  fact.addModel(BOX, new Cube(*skybox), BOX_TEXTURE);
  fact.addModel(FLAME, new Cube(*skybox), FLAME_TEXTURE);
  fact.addModel(SPEEDITEM, SPEEDITEM_MODEL);
  fact.addModel(HEALTHITEM, HEALTHITEM_MODEL);
  fact.addModel(CHARACTER, CHARACTER_MODEL);
  fact.addModel(BOMB, BOMB_MODEL);
  items->addItem(SPEEDITEM, new SpeedItem(0, 0, _gameInfo));
  items->addItem(HEALTHITEM, new HealthItem(0, 0, _gameInfo));


  Camera *all_cam[1] = { &_cam };

  _gameInfo.map.createMap(_gameInfo);
  spawn.spawnEnt(1, 0, all_cam, _gameInfo);
  createDisplayBorder();
  return (true);
}

void	GameEngine::mainInput()
{
  t_window	win;

  _gameInfo.input.getInput(_gameInfo.set);
  if ((_gameInfo.input[win] && win.event == WIN_QUIT) || _gameInfo.input[SDLK_ESCAPE])
    {
      _shutdown = true;
      v_Contcit end = _gameInfo.map.ContEnd();
      for (v_Contcit it = _gameInfo.map.ContBegin();it != end;it++)
	{
	  AEntity *ent;
	  v_Entit its;
	  l_Entit itm;
	  while ((ent = (*it)->listFront()) != NULL)
	    ent->setDestroy();
	  while ((ent = (*it)->vecFront()) != NULL)
	    {
	      ent->setDestroy();
	      _gameInfo.map.pushToCollector(ent);
	    }
	}
      return ;
    }
}

int		GameEngine::clearElements()
{
  return (_gameInfo.map.clearElements());
}

bool		GameEngine::update()
{
  double	time;
  double	fps = (1000 / _gameInfo.set.getVar(FPS));

  mainInput();
  _gameInfo.condvar->broadcast();
  if (clearElements() == 0 && _shutdown)
    return (false);
  _frames++;
  if ((time = _gameInfo.clock.getElapsed()) < fps)
    {
      _text << round(_frames / _gameInfo.clock.getElapsed());
      _frames = 0;
      usleep((fps - time) * 1000);
    }
  _win->updateClock(_gameInfo.clock);
  return (true);
}

void GameEngine::draw()
{
  glm::mat4 model = glm::transpose(glm::translate(glm::mat4(1.0f), _cam.getPosView()));

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  _cam.lookAt();
  _shader.bind();
  _shader.setUniform("projection", _cam.getProjection());
  _shader.setUniform("view", _cam.getTransformation());
  _shader.setUniform("model", model);
  _shader.setUniform("inv_model", glm::inverse(model));
  for (std::vector<IObject *>::const_iterator it = _obj.begin(); it != _obj.end(); it++)
    (*it)->draw(_shader, _gameInfo.clock);
  v_Contcit end = _gameInfo.map.ContEnd();
  for (v_Contcit it = _gameInfo.map.ContBegin();it != end;it++)
    {
      Mutex *mutex = (*it)->getMutex();
      Scopelock	<Mutex>sc(*mutex);
      v_Entcit end_vector = (*it)->vecEnd();
      l_Entcit end_list = (*it)->listEnd();
      for (v_Entcit it1 = (*it)->vecBegin();it1 != end_vector;it1++)
	(*it1)->draw(_shader, _gameInfo.clock);
      for (l_Entcit it1 = (*it)->listBegin();it1 != end_list;it1++)
	(*it1)->draw(_shader, _gameInfo.clock);
    }
  _textShader->bind();
  _textShader->setUniform("projection", glm::ortho(0.0f, 1600.0f, 900.0f, 0.0f, -1.0f, 1.0f));
  _textShader->setUniform("view", glm::mat4(1));
  _text.draw(*_textShader, _gameInfo.clock);
  _win->flush();
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
