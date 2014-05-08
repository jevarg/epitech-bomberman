#include <iostream>
#include "GameEngine.hpp"

GameEngine::GameEngine()
  : _cam(), _cube("./assets/texture.tga"), _skybox("./assets/skybox.tga")
{

}

GameEngine::~GameEngine()
{
  _win.stop();
}

bool GameEngine::initialize()
{
  _mapX = 1;
  _mapY = 1;
  if (!_win.start(800, 600, "Bomberman"))
    throw(Exception("Cannot open window"));
  glEnable(GL_DEPTH_TEST);
  if (!_shader.load("./Shaders/basic.fp", GL_FRAGMENT_SHADER)
   || !_shader.load("./Shaders/basic.vp", GL_VERTEX_SHADER) || !_shader.build())
    return (false);
  _cam.initialize();
  _cam.translate(glm::vec3(0, 10, -30));

  _skybox.initialize();
  _skybox.scale(glm::vec3(500, 500, 500));

  _model.load("assets/marvin.fbx");

  IObject *obj = new Model(_model);
  obj->translate(glm::vec3(2.0, -1.0, 0));
  obj->scale(glm::vec3(0.005, 0.005, 0.005));
  _obj.push_back(obj);

  if (_cube.initialize() == false)
    return (false);
  for (int y = 0;y < _mapY;y++)
    for (int x = 0;x < _mapX;x++)
      {
  	IObject *obj = new Cube(_cube);
  	obj->translate(glm::vec3(y * 2, 0.0, x * 2));
  	_obj.push_back(obj);
      }
  // _map.createMap();
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
