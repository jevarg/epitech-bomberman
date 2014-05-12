#include <SDL.h>
#include "Input.hpp"

Input::Input()
{
  for (unsigned int i = FORWARD; i < UNKNOWN; ++i)
    _actionState.push_back(false);
  _boundKey.insert(std::pair<keyCode, bool>(SDLK_BACKSPACE, false));
  _boundKey.insert(std::pair<keyCode, bool>(SDLK_ESCAPE, false));
}

Input::~Input()
{
}

void	Input::handleEvent(const Settings &set, const SDL_Event &event, bool state)
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

void	Input::getInput(const Settings &set)
{
  SDL_Event	event;

  if (SDL_PollEvent(&event))
    {
      if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP)
	handleEvent(set, event, event.type == SDL_KEYDOWN);
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
