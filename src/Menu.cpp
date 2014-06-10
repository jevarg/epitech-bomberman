#include "Menu.hpp"

Menu::Menu(Settings &set): _win(), _input(), _set(set), _textShader(), _done(false), _sound(), _console(_set)
{
  _frames = 0;
}

Menu::~Menu()
{
}

bool  Menu::initialize()
{
  if (!_win.start(_set.getVar(W_WIDTH), _set.getVar(W_HEIGHT), "Bomberman"))
    throw(Exception("Cannot open window"));
  glEnable(GL_DEPTH_TEST);
  if (!_textShader.load("./Shaders/text.fp", GL_FRAGMENT_SHADER) ||
      !_textShader.load("./Shaders/text.vp", GL_VERTEX_SHADER) ||
      !_textShader.build())
    return (false);
  if (!_text.initialize())
    return (false);
  return (true);
  // fill Panels vectors with Widgets
}

bool  Menu::update()
{
  double time;
  double fps = (1000 / _set.getVar(FPS));

  _input.getInput(_set);
  _win.updateClock(_clock);
  if (_input[LAUNCHGAME])
    launchGame();
  if (_input[SDLK_F1])
    _console.aff(_clock, _textShader, _win, _input);
  if (_input[SDLK_ESCAPE]) // || _input.getInput(SDL_QUIT))
    return (false);
  _frames++;
  if ((time = _clock.getElapsed()) < fps)
    {
      _text.setText("Play", 50.0f, 50.0f, 40.0f);
      _frames = 0;
      usleep((fps - time) * 1000);
    }
  return (true);
}

void  Menu::draw()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glDisable(GL_DEPTH_TEST);
  _textShader.bind();
  _textShader.setUniform("projection", glm::ortho(0.0f, 1600.0f, 900.0f, 0.0f, -1.0f, 1.0f));
  _textShader.setUniform("view", glm::mat4(1));
  _text.draw(_textShader, _clock);
  glEnable(GL_DEPTH_TEST);
  _win.flush();
}

void	Menu::launchGame()
{
  Map map(_set);
  GameEngine eng(&_win, &_clock, &_textShader, &map, &_set, &_input, &_sound);
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
