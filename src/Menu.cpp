#include "Menu.hpp"

Menu::Menu(Settings &set): _win(), _input(), _set(set), _shader(), _done(false)
{

}

Menu::~Menu()
{
}

bool  Menu::initialize()
{
  if (!_win.start(_set.getVar(W_WIDTH), _set.getVar(W_HEIGHT), "Bomberman",
		  SDL_INIT_VIDEO, SDL_WINDOW_OPENGL))
    throw(Exception("Cannot open window"));
  glEnable(GL_DEPTH_TEST);
  if (!_shader.load("./Shaders/basic.fp", GL_FRAGMENT_SHADER)
   || !_shader.load("./Shaders/basic.vp", GL_VERTEX_SHADER) || !_shader.build())
    return (false);
  // if (!_text.initialize())
  //   return (false);
  // _text.write("TEST", 0, 0, 1.0);
  return (true);
}

bool  Menu::update()
{
  double time;
  double fps = (1000 / _set.getVar(FPS));

  _input.getInput(_set);
  _win.updateClock(_clock);
  if (_input[LAUNCHGAME])
    launchGame();
  if (_input[SDLK_ESCAPE]) // || _input.getInput(SDL_QUIT))
    return (false);
  if ((time = _clock.getElapsed()) < fps)
    usleep((fps - time) * 1000);
  return (true);
}

void  Menu::draw()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  // _shader.bind();
  // _shader.setUniform("view", glm::mat4(1));
  // _text.draw(_shader, _clock);
  _win.flush();
}

void	Menu::launchGame()
{
  Map map(_set);
  GameEngine eng(&_win, _clock, &_shader, map, _set, _input);
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
