#include <iostream>
#include "GameEngine.hpp"

GameEngine::GameEngine(Settings &set, Input &input)
    : _save(), _cam(), _map(set), _set(set),
      _input(input), _type(), _texture()
{
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
  Cube *skybox;

  _mapX = _set.getVar(MAP_HEIGHT);
  _mapY = _set.getVar(MAP_WIDTH);
  if (!_win.start(_set.getVar(W_WIDTH), _set.getVar(W_HEIGHT), "Bomberman"))
    throw(Exception("Cannot open window"));
  glEnable(GL_DEPTH_TEST);
  if (!_shader.load("./Shaders/basic.fp", GL_FRAGMENT_SHADER)
   || !_shader.load("./Shaders/basic.vp", GL_VERTEX_SHADER) || !_shader.build())
    return (false);
  _cam.initialize();
  _cam.translate(glm::vec3(0, 5, -10));

  skybox = new Cube(SKY_TEXTURE);
  skybox->initialize();
  skybox->scale(glm::vec3(500, 500, 500));
  _obj.push_back(skybox);

  _type[WALL] = new Cube(*skybox);
  _type[BOX] = new Cube(*skybox);
  _type[CHARACTER] = new Cube(*skybox);
  _texture[WALL] = new gdl::Texture();
  _texture[BOX] = new gdl::Texture();
  _texture[GROUND] = new gdl::Texture();

  skybox = new Cube(*skybox);
  skybox->translate(glm::vec3(_mapX - 1, -1.0, _mapY - 1));
  skybox->scale(glm::vec3(_mapX, 0.0, _mapY));
  _obj.push_back(skybox);

  if (!_texture[WALL]->load(WALL_TEXTURE, true)
      || !_texture[BOX]->load(BOX_TEXTURE, true)
      || !_texture[GROUND]->load(GROUND_TEXTURE, true))
    throw(Exception("Cannot load the texture"));

  _type[WALL]->setTexture(_texture[WALL]);
  _type[BOX]->setTexture(_texture[BOX]);

  if (!_model.load("./assets/steve.fbx"))
    return (false);
  _model.translate(glm::vec3(-5.0, 0, 0));

  _map.createMap(_type);
  createDisplayBorder();
  _obj.push_back(&_model);
  return (true);
}

bool GameEngine::update()
{
  int time;
  double fps = (1000 / _set.getVar(FPS));
  t_mouse mouse;

  _input.getInput(_set);
  if (_input[SDLK_ESCAPE])
    return (false);
  if (_input[SDLK_o])
    _model.rotate(glm::vec3(0, 1.0, 0), 5);
  if (_input[SDLK_p])
    _model.rotate(glm::vec3(0, 1.0, 0), -5);
  if (_input[mouse])
    std::cout << "catched event " << mouse.event << std::endl;
  if ((time = _clock.getElapsed()) < fps)
    usleep((fps - time) * 1000);
  _win.updateClock(_clock);
  _cam.update(_clock, _input);
  // for (size_t i = 0; i < _obj.size(); ++i)
  //   _obj[i]->update(_clock, _input);
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
    (*it)->draw(_shader, _clock);
  v_Contcit end = _map.ContEnd();
  for (v_Contcit it = _map.ContBegin();it != end;it++)
    {
      v_Entcit end_vector = (*it)->vecEnd();
      l_Entcit end_list = (*it)->listEnd();
      for (v_Entcit it1 = (*it)->vecBegin();it1 != end_vector;it1++)
	(*it1)->draw(_shader, _clock);
      for (l_Entcit it1 = (*it)->listBegin();it1 != end_list;it1++)
	(*it1)->draw(_shader, _clock);
    }
  _win.flush();
}

void GameEngine::createDisplayBorder()
{
  unsigned int	i;

  for (i = 0; i < _mapX; ++i)
    {
      _obj.push_back(_type[WALL]->clone());
      _obj.back()->translate(glm::vec3(2 * i, 0.0, 0));
      _obj.push_back(_type[WALL]->clone());
      _obj.back()->translate(glm::vec3(2 * i, 0.0, 2 * (_mapY - 1)));
    }
  for (i = 1; i < (_mapY - 1); ++i)
    {
      _obj.push_back(_type[WALL]->clone());
      _obj.back()->translate(glm::vec3(2 * (_mapX - 1), 0.0, 2 * i));
      _obj.push_back(_type[WALL]->clone());
      _obj.back()->translate(glm::vec3(0, 0.0, 2 * i));
    }
}
