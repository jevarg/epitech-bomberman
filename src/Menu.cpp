#include "Menu.hpp"

Menu::Menu(): _win(), _input(),  _shader(), _done(false)
{

}

Menu::~Menu()
{
}

bool  Menu::initialize()
{
  if (!_win.start(1920, 1080, "Bomberman", SDL_INIT_VIDEO, SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN))
    throw(Exception("Cannot open window"));
  glEnable(GL_DEPTH_TEST);
  if (!_shader.load("./Shaders/basic.fp", GL_FRAGMENT_SHADER)
   || !_shader.load("./Shaders/basic.vp", GL_VERTEX_SHADER) || !_shader.build())
    return (false);
  return (true);
}

bool  Menu::update()
{
  double time;
  double fps = (1000 / FPS);

  if (_input.getKey(SDLK_g))
    launchGame();
  if (_input.getKey(SDLK_ESCAPE) || _input.getInput(SDL_QUIT))
    return (false);
  _win.updateClock(_clock);
  _win.updateInputs(_input);
  if ((time = _clock.getElapsed()) < fps)
    usleep((fps - time) * 1000);
  return (true);
}

void  Menu::draw()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  // _shader.bind();
  // _shader.setUniform("view", glm::mat4(1));
  _win.flush();
}

void	Menu::launchGame()
{
  GameEngine eng(&_win, &_input, &_clock, &_shader);
  bool	done = true;

  if (!eng.initialize())
    return ;
  while ((done = eng.update()))
    eng.draw();
}

void	Menu::launch()
{
  if (!initialize())
    return ;
  while (!_done)
    {
      if (update() == false)
	return ;
      draw();
    }
  _win.stop();
}
