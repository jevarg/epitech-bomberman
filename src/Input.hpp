#ifndef _INPUT_H_
# define _INPUT_H_

# include <SDL.h>
# include "Settings.hpp"

enum	eMouse
  {
    NONE = 0,
    MOTION,
    BUTTONDOWN,
    BUTTONUP,
    WHEEL
  };

enum	eWin
  {
    WIN_QUIT = 0,
    WIN_RESIZE,
    WIN_NONE
  };

typedef struct	s_mouse
{
  int		x;
  int		y;
  char		button;
  char		click;
  eMouse	event;
}		t_mouse;

typedef struct	s_window
{
  eWin		event;
  int		x;
  int		y;
}		t_window;

class Input
{
public:
  Input();
  ~Input();

  void	getInput(const Settings &set);
  bool	operator[](eAction act) const;
  bool	operator[](t_mouse &key) const;
  bool	operator[](t_window &win) const;
  bool	operator[](SDL_Keycode key) const;

private:
  void	keyboardInput(const Settings &set, const SDL_Event &event, bool state);
  void	mouseInput(const SDL_Event &event);
  void	windowEvent(const SDL_Event &event);
  std::vector<bool>		_actionState;
  SDL_Keycode			_key;
  t_mouse			_mouse;
  t_window			_window;
};

#endif /* _INPUT_H_ */
