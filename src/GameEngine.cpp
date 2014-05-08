#include <iostream>
#include "GameEngine.hpp"

GameEngine::GameEngine(): _save(), _cam()
{

}

GameEngine::~GameEngine()
{
  _win.stop();
}

bool GameEngine::initialize()
{
  if (!_win.start(800, 600, "Bomberman"))
    throw(Exception("Cannot open window"));
  glEnable(GL_DEPTH_TEST);
  if (!_shader.load("./Shaders/basic.fp", GL_FRAGMENT_SHADER)
   || !_shader.load("./Shaders/basic.vp", GL_VERTEX_SHADER) || !_shader.build())
    return (false);
  _cam.initialize(glm::vec3(0, 10, -30), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
  _shader.bind();
  _shader.setUniform("view", _cam.getTransformation());
  _shader.setUniform("projection", _cam.getProjection());

  AObject *cube = new Cube();
  if (cube->initialize() == false)
    return (false);
  _obj.push_back(cube);
  return (true);
}

bool GameEngine::update()
{
  int time;
  double fps = (1000 / FPS);

  if (_input.getInput(SDL_QUIT) || _input.getKey(SDLK_ESCAPE))
    return (false);
  if ((time = _clock.getElapsed()) < fps)
    usleep((fps - time) * 1000);
  _win.updateClock(_clock);
  _win.updateInputs(_input);
  for (size_t i = 0; i < _obj.size(); ++i)
    _obj[i]->update(_clock, _input);
  return (true);
}

void GameEngine::draw()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  _shader.bind();
  for (size_t i = 0; i < _obj.size(); ++i)
    _obj[i]->draw(_shader, _clock);
  _win.flush();
  std::vector<Container *>::const_iterator toto;

  _save.saveGame(toto, "toto");
  _save.loadGame(this, "toto");
  exit(0);
}

void	GameEngine::addEntitie(AEntitie *ent)
{
  int	ratiox;
  int	ratioy;
  unsigned int	pos;
  Container	*cont;

  ratiox = ent->getXPos() / SQUARESIZE;
  ratioy = ent->getYPos() / SQUARESIZE;
  pos = ratioy * (_mapX / SQUARESIZE) + ratiox;
  while (_cont.size() <= pos)
    {
      cont = new Container;
      _cont.push_back(cont);
    }
  _cont[pos]->stockEntitie(ent);
}
