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

void	Input::getInput(const Settings &set)
{
  SDL_Event	event;
  SDL_Keycode	keyPressed;
  std::map<keyCode, bool>::iterator it;
  std::map<keyCode, bool>::iterator end;
  eAction	act;

  if (SDL_PollEvent(&event))
    {
      if (event.type == SDL_KEYDOWN)
	{
	  keyPressed = event.key.keysym.sym;
	  if ((act = set.getActionFromKey(keyPressed)) != UNKNOWN)
	    _actionState[act] = true;
	  for (it = _boundKey.begin(), end = _boundKey.end(); it != end; ++it)
	    {
	      if (it->first == keyPressed)
		{
		  it->second = true;
		  break ;
		}
	    }
	}
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
