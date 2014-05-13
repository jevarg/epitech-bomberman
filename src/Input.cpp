#include <SDL.h>
#include <cstring>
#include "Input.hpp"

Input::Input()
{
  for (unsigned int i = FORWARD; i < UNKNOWN; ++i)
    _actionState.push_back(false);
  _boundKey.insert(std::pair<keyCode, bool>(SDLK_BACKSPACE, false));
  _boundKey.insert(std::pair<keyCode, bool>(SDLK_ESCAPE, false));
  std::memset(&_mouse, 0, sizeof(_mouse));
}

Input::~Input()
{
}

void	Input::keyboardInput(const Settings &set, const SDL_Event &event, bool state)
{
  std::map<keyCode, bool>::iterator it;
  std::map<keyCode, bool>::iterator end;
  SDL_Keycode	key = event.key.keysym.sym;
  eAction	act;

  if ((act = set.getActionFromKey(key)) != UNKNOWN)
    _actionState[act] = state;
  for (it = _boundKey.begin(), end = _boundKey.end(); it != end; ++it)
    {
      if (it->first == key)
	{
	  it->second = state;
	  break ;
	}
    }
}

void	Input::mouseInput(SDL_Event &event)
{
  switch (event.type)
    {
    case SDL_MOUSEMOTION:
      _mouse.x = event.motion.x;
      _mouse.y = event.motion.y;
      _mouse.event = MOTION;
      break ;
    case SDL_MOUSEBUTTONDOWN:
      _mouse.x = event.button.x;
      _mouse.y = event.button.y;
      _mouse.button = event.button.button;
      _mouse.click = event.button.clicks;
      _mouse.event = BUTTONDOWN;
      break ;
    case SDL_MOUSEBUTTONUP:
      if (_mouse.event == BUTTONDOWN)
	{
	  _mouse.x = event.button.x;
	  _mouse.y = event.button.y;
	  _mouse.event = BUTTONUP;
	}
      else
	_mouse.event = NONE;
      break ;
    case SDL_MOUSEWHEEL:
      _mouse.x = event.wheel.x;
      _mouse.y = event.wheel.y;
      _mouse.event = WHEEL;
      break ;
   default:
      _mouse.event = NONE;
      break ;
    }
}

void	Input::getInput(const Settings &set)
{
  SDL_Event	event;

  if (_mouse.event != BUTTONDOWN)
    _mouse.event = NONE;
  while (SDL_PollEvent(&event))
    {
      if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP)
	keyboardInput(set, event, event.type == SDL_KEYDOWN);
      mouseInput(event);
    }
}

bool	Input::operator[](eAction act)
{
  return (_actionState[static_cast<int>(act)]);
}

bool	Input::operator[](keyCode key)
{
  std::map<keyCode, bool>::const_iterator	it;

  if ((it = _boundKey.find(key)) == _boundKey.end())
    return (false);
  return (it->second);
}

bool	Input::operator[](t_mouse &mouse)
{
  if (_mouse.event == NONE)
    return (false);
  mouse = _mouse;
  return (true);
}
