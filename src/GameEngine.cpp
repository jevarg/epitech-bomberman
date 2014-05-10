#include <iostream>
#include "GameEngine.hpp"

GameEngine::GameEngine()
  : _cam(), _skybox(SKY_TEXTURE), _type(), _texture()
{
}


GameEngine::~GameEngine()
{
  _win.stop();
}

bool GameEngine::initialize()
{
  _mapX = 10;
  _mapY = 10;
  if (!_win.start(800, 600, "Bomberman"))
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
  _texture[WALL] = new gdl::Texture();
  _texture[BOX] = new gdl::Texture();
  _texture[GROUND] = new gdl::Texture();

  if (!_texture[WALL]->load(WALL_TEXTURE, true)
      || !_texture[BOX]->load(BOX_TEXTURE, true)
      || !_texture[GROUND]->load(GROUND_TEXTURE, true))
    throw(Exception("Cannot load the texture"));

  _type[WALL]->setTexture(_texture[WALL]);
  _type[BOX]->setTexture(_texture[BOX]);

  if (!_model.load("./assets/marvin.fbx"))
    return (false);
  _model.scale(glm::vec3(0.005, 0.005, 0.005));

  _map.createMap();
  createDisplayMap();
  _obj.push_back(&_model);
  return (true);
}

bool GameEngine::update()
{
  double time;
  double fps = (1000 / FPS);

  if (_input.getInput(SDL_QUIT) || _input.getKey(SDLK_ESCAPE))
    return (false);
  if ((time = _clock.getElapsed()) < fps)
    usleep((fps - time) * 1000);
  _win.updateClock(_clock);
  _win.updateInputs(_input);
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

void GameEngine::createDisplayMap()
{
  v_Contcit	end = _map.ContEnd();
  IObject	*ground = new Cube(_skybox);

  ground->setTexture(_texture[GROUND]);
  ground->scale(glm::vec3(2 * _mapX, 1.0, 2 * _mapY));
  ground->translate(glm::vec3(2 * (_mapX - 0.5), -2.0, 2 * (_mapY - 0.5)));
  _obj.push_back(ground);
  for (v_Contcit it = _map.ContBegin();it != end;++it)
    {
      l_Entcit endList = (*it)->listEnd();
      for (l_Entcit it1 = (*it)->listBegin();it1 != endList;++it1)
	if (_type[(*it1)->_type])
	  {
	    _obj.push_back(_type[(*it1)->_type]->clone());
	    _obj.back()->translate(glm::vec3(2 * (*it1)->_x, 0.0, 2 * (*it1)->_y));
	  }
      v_Entcit endVec = (*it)->vecEnd();
      for (v_Entcit it1 = (*it)->vecBegin();it1 != endVec;++it1)
	if (_type[(*it1)->_type])
	  {
	    _obj.push_back(_type[(*it1)->_type]->clone());
	    _obj.back()->translate(glm::vec3(2 * (*it1)->_x, 0.0, 2 * (*it1)->_y));
	  }
    }
}
