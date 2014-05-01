#include <iostream>
#include "GameEngine.hpp"

GameEngine::~GameEngine()
{
  _win.stop();
}

bool GameEngine::initialize()
{
  _win.start(800, 600, "Bomberman");
  return (true);
}

bool GameEngine::update()
{
  int time;
  double fps = (1000 / FPS);

  if (_input.getInput(SDL_QUIT))
    return (false);
  if ((time = _clock.getElapsed()) < fps)
    usleep((fps - time) * 1000);
  _win.updateClock(_clock);
  _win.updateInputs(_input);
  return (true);
}

void GameEngine::draw()
{

}
