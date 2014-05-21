#include <iostream>
#include "GameEngine.hpp"

GameEngine::GameEngine(gdl::Clock &clock, Map &map, Settings &set, Input &input)
  : _save(), _lua(), _type(), _texture(),
    _gameInfo(clock, map, set, input)
{
  _gameInfo.mutex = new Mutex;
  _gameInfo.condvar = new Condvar;
}

GameEngine::~GameEngine()
{
  while (_obj.size())
    {
      delete _obj.back();
      _obj.pop_back();
    }
  _win.stop();
}

bool GameEngine::initialize()
{
  Cube *skybox;
  Spawn	spawn(_gameInfo.map);

  _mapX = _gameInfo.set.getVar(MAP_HEIGHT);
  _mapY = _gameInfo.set.getVar(MAP_WIDTH);
  if (!_win.start(_gameInfo.set.getVar(W_WIDTH),
		  _gameInfo.set.getVar(W_HEIGHT), "Bomberman"))
    throw(Exception("Cannot open window"));
  glEnable(GL_DEPTH_TEST);
  if (!_shader.load("./Shaders/basic.fp", GL_FRAGMENT_SHADER)
   || !_shader.load("./Shaders/basic.vp", GL_VERTEX_SHADER) || !_shader.build())
    return (false);
  _cam.translate(glm::vec3(0, 5, -10));

  skybox = new Cube(SKY_TEXTURE);
  skybox->initialize();
  skybox->scale(glm::vec3(500, 500, 500));
  _obj.push_back(skybox);

  _model = new Model();
  if (!_model->load("./assets/marvin.fbx"))
    return (false);

  _type[WALL] = new Cube(*skybox);
  _type[BOX] = new Cube(*skybox);
  _type[CHARACTER] = _model;
  _texture[WALL] = new gdl::Texture();
  _texture[BOX] = new gdl::Texture();
  _texture[GROUND] = new gdl::Texture();

  skybox = new Cube(*skybox);
  skybox->translate(glm::vec3((((float)(_mapX) - 1.0) / 2.0),
			      -0.5, (((float)(_mapY) - 1.0) / 2.0)));
  skybox->scale(glm::vec3(_mapX, 0.0, _mapY));
  _obj.push_back(skybox);

  if (!_texture[WALL]->load(WALL_TEXTURE, true)
      || !_texture[BOX]->load(BOX_TEXTURE, true)
      || !_texture[GROUND]->load(GROUND_TEXTURE, true))
    throw(Exception("Cannot load the texture"));

  _type[WALL]->setTexture(_texture[WALL]);
  _type[BOX]->setTexture(_texture[BOX]);

  Camera *all_cam[1] = { &_cam };

  _gameInfo.map.createMap(_type);
  spawn.spawnEnt(1, 0, _type, all_cam, _gameInfo);
  createDisplayBorder();
  return (true);
}

void GameEngine::prepareIA(int level)
{
  int cnt = 0;
  int aggro[] = {4, 8, 12, 10};
  for (std::vector<Container*>::const_iterator cont_it = _gameInfo.map.ContBegin() ; cont_it != _gameInfo.map.ContEnd() ; ++cont_it)
    for (l_Entcit ent_it = (*cont_it)->listBegin() ; ent_it != (*cont_it)->listEnd() ; ++ent_it)
      {
	if ((*ent_it)->getType() == CHARACTER)
	  {
	    int y = (*ent_it)->getYPos() - aggro[level - 1];
	    int x = (*ent_it)->getYPos() - aggro[level - 1];
	    int c1 = 1;
	    int c2 = 1;
	    cnt = 0;
	    if (y < 1)
	      y = 1;
	    if (x < 1)
	      x = 1;
	    for (int i = y ; i < y + (aggro[level - 1] * 2) &&
		   i < static_cast<int>(_mapY) - 1 ; ++i)
	      {
		c2 = 1;
		for (int j = x ; j < x + (aggro[level - 1] * 2) &&
		       j < static_cast<int>(_mapX) - 1 ; ++j)
		  {
		    if (cnt == 0)
		      _lua.pushCreateTable((aggro[level - 1] * 2) * (aggro[level - 1] * 2) + 4);
		    _lua.pushIntInt(++cnt, (*cont_it)->checkColision(j, i));
		    _lua.pushIntInt(++cnt, c1);
		    _lua.pushIntInt(++cnt, c2);
		    ++c2;
		  }
		++c1;
	      }
	    if (cnt != 0)
	      {
		_lua.pushStringInt("bomb_range", 4);
		_lua.pushStringInt("x", (*ent_it)->getXPos());
		_lua.pushStringInt("y", (*ent_it)->getYPos());
		_lua.pushStringInt("level", level);
		_lua.pushStringInt("aggro", aggro[level - 1]);
		_lua.pushSetGlobal("arg");
		_lua.executeLua("ai/main.lua");
		_lua.getDatas();
		// call new action
	      }
	  }
      }
  exit(0);
}

bool GameEngine::update()
{
  int	time;
  double	fps = (1000 / _gameInfo.set.getVar(FPS));
  t_mouse	mouse;
  t_window	win;

  prepareIA(2);
  _gameInfo.input.getInput(_gameInfo.set);
  if ((_gameInfo.input[win] && win.event == WIN_QUIT) || _gameInfo.input[SDLK_ESCAPE])
    {
      v_Contcit end = _gameInfo.map.ContEnd();
      for (v_Contcit it = _gameInfo.map.ContBegin();it != end;it++)
	{
	  l_Entit end_list = (*it)->listEndMod();
	  for (l_Entit it1 = (*it)->listBeginMod(); it1 != end_list; it1++)
	    (*it1)->destroy();
	}
      return (false);
    }
  if (_gameInfo.input[DROPBOMB])
    {
      std::cout << "DROP THE BOMB" << std::endl;
      _gameInfo.map.addEntity(new Entity(rand() % 10, rand() % 10, WALL, _obj[WALL]->clone()));
    }
  if (_gameInfo.input[mouse])
    std::cout << "catched event " << mouse.event << std::endl;
  // if (win.event == WIN_RESIZE) // Seems not to work
  //   std::cout << "Resize to: " << win.x << " " << win.y << std::endl;
  if ((time = _gameInfo.clock.getElapsed()) < fps)
    usleep((fps - time) * 1000);
  _win.updateClock(_gameInfo.clock);
  return (true);
}

void GameEngine::draw()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  _cam.lookAt();
  _shader.setUniform("view", _cam.getTransformation());
  _shader.setUniform("projection", _cam.getProjection());
  _shader.bind();
  for (std::vector<IObject *>::const_iterator it = _obj.begin(); it != _obj.end(); it++)
    (*it)->draw(_shader, _gameInfo.clock);
  //std::cout << " BEGIN "<< std::endl;
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
  //  std::cout << " END "<< std::endl;
  _win.flush();
}

void GameEngine::createDisplayBorder()
{
  unsigned int	i;

  for (i = 0; i < _mapX; ++i)
    {
      _obj.push_back(_type[WALL]->clone());
      _obj.back()->translate(glm::vec3(i, 0.0, 0));
      _obj.push_back(_type[WALL]->clone());
      _obj.back()->translate(glm::vec3(i, 0.0, (_mapY - 1)));
    }
  for (i = 1; i < (_mapY - 1); ++i)
    {
      _obj.push_back(_type[WALL]->clone());
      _obj.back()->translate(glm::vec3((_mapX - 1), 0.0, i));
      _obj.push_back(_type[WALL]->clone());
      _obj.back()->translate(glm::vec3(0, 0.0, i));
    }
}
