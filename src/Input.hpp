#ifndef _INPUT_H_
# define _INPUT_H_

# include <SDL.h>
# include <list>
# include <algorithm>
# include "Settings.hpp"
# include "Mutex.hpp"
# include "Scopelock.hpp"

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

typedef std::list<SDL_Keycode>::const_iterator	l_Keycit;
typedef std::list<SDL_Keycode>::iterator       	l_Keyit;

class Input
{
public:
  Input();
  ~Input();

  void	getInput(const Settings &set);
  bool	isPressed(Keycode key);
  const l_Keycit	getPressedBeg() const;
  const l_Keycit	getPressedEnd() const;
  bool	operator[](eAction act) const;
  bool	operator[](t_mouse &key) const;
  bool	operator[](t_window &win) const;
  void	operator[](Keycode * const key) const;

private:
  void	keyboardInput(const Settings &set, const SDL_Event &event, bool state);
  void	mouseInput(const SDL_Event &event);
  void	windowEvent(const SDL_Event &event);
  void	pressKey(const SDL_Event &event);
  void	unpressKey();

  Mutex				_mutex;
  std::vector<bool>		_actionState;
  std::list<Keycode>		_keyPressed;
  Keycode			_key;
  t_mouse			_mouse;
  t_window			_window;
};

#endif /* _INPUT_H_ */
