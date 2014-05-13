#include <iostream>
#include "GameEngine.hpp"

GameEngine::GameEngine(Settings &set, Input &input)
    : _save(), _cam(), _skybox(SKY_TEXTURE), _map(set), _set(set),
      _input(input), _type(), _texture()
{
}


GameEngine::~GameEngine()
{
  _win.stop();
}

bool GameEngine::initialize()
{
  _mapX = 15;
  _mapY = 15;
  if (!_win.start(_set.getVar(W_WIDTH), _set.getVar(W_HEIGHT), "Bomberman"))
    throw(Exception("Cannot open window"));
  glEnable(GL_DEPTH_TEST);
  if (!_shader.load("./Shaders/basic.fp", GL_FRAGMENT_SHADER)
   || !_shader.load("./Shaders/basic.vp", GL_VERTEX_SHADER) || !_shader.build())
    return (false);
  _cam.initialize();
  _cam.translate(glm::vec3(0, 5, -10));

  _skybox.initialize();
  _skybox.scale(glm::vec3(500, 500, 500));

  _type[WALL] = new Cube(_skybox);
  _type[BOX] = new Cube(_skybox);
  _type[CHARACTER] = new Cube(_skybox);
  _texture[WALL] = new gdl::Texture();
  _texture[BOX] = new gdl::Texture();
  _texture[GROUND] = new gdl::Texture();

  if (!_texture[WALL]->load(WALL_TEXTURE, false)
      || !_texture[BOX]->load(BOX_TEXTURE, false)
      || !_texture[GROUND]->load(GROUND_TEXTURE, false))
    throw(Exception("Cannot load the texture"));

  _type[WALL]->setTexture(_texture[WALL]);
  _type[BOX]->setTexture(_texture[BOX]);

  if (!_model.load("./assets/steve.fbx"))
    return (false);
  _model.translate(glm::vec3(-5.0, 0, 0));

  _map.createMap();
  createDisplayMap();
  _obj.push_back(&_model);
  return (true);
}

bool GameEngine::update()
{
  int time;
  double fps = (1000 / CFPS);

  _input.getInput(_set);
  if (_input[SDLK_ESCAPE])
    return (false);
  if (_input[SDLK_o])
    _model.rotate(glm::vec3(0, 1.0, 0), 5);
  if (_input[SDLK_p])
    _model.rotate(glm::vec3(0, 1.0, 0), -5);
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
  _skybox.draw(_shader, _clock);
  for (std::vector<IObject *>::const_iterator it = _obj.begin(); it != _obj.end(); it++)
    (*it)->draw(_shader, _clock);
  _win.flush();
}

void GameEngine::createDisplayBorder()
{
  unsigned int	mapX = _map.getWidth();
  unsigned int	mapY = _map.getHeight();
  unsigned int	i;

  for (i = 0; i < mapX; ++i)
    {
      _obj.push_back(_type[WALL]->clone());
      _obj.back()->translate(glm::vec3(2 * i, 0.0, 0));
      _obj.push_back(_type[WALL]->clone());
      _obj.back()->translate(glm::vec3(2 * i, 0.0, 2 * (mapY - 1)));
    }
  for (i = 1; i < (mapY - 1); ++i)
    {
      _obj.push_back(_type[WALL]->clone());
      _obj.back()->translate(glm::vec3(2 * (mapX - 1), 0.0, 2 * i));
      _obj.push_back(_type[WALL]->clone());
      _obj.back()->translate(glm::vec3(0, 0.0, 2 * i));
    }
}

void GameEngine::createDisplayMap()
{
  v_Contcit	end = _map.ContEnd();
  IObject	*ground = new Cube(_skybox);

  ground->scale(glm::vec3(2 * _mapX, 1.0, 2 * _mapY));
  ground->translate(glm::vec3(2 * (_mapX - 0.5), -2.0, 2 * (_mapY - 0.5)));
  _obj.push_back(ground);
  createDisplayBorder();
  for (v_Contcit it = _map.ContBegin(); it != end; ++it)
    {
      l_Entcit endList = (*it)->listEnd();
      for (l_Entcit it1 = (*it)->listBegin(); it1 != endList; ++it1)
	if (_type[(*it1)->getType()])
	  {
	    _obj.push_back(_type[(*it1)->getType()]->clone());
	    _obj.back()->translate(glm::vec3(2 * (*it1)->getXPos(),
					     0.0, 2 * (*it1)->getYPos()));
	  }
      v_Entcit endVec = (*it)->vecEnd();
      for (v_Entcit it1 = (*it)->vecBegin(); it1 != endVec; ++it1)
	if (_type[(*it1)->getType()])
	  {
	    _obj.push_back(_type[(*it1)->getType()]->clone());
	    _obj.back()->translate(glm::vec3(2 * (*it1)->getXPos(), 0.0,
					     2 * (*it1)->getYPos()));
	  }
    }
}
