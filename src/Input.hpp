#ifndef _INPUT_H_
# define _INPUT_H_

# include "Settings.hpp"

enum	eMouse
  {
    NONE = 0,
    MOTION,
    BUTTONDOWN,
    BUTTONUP,
    WHEEL
  };

typedef struct	s_mouse
{
  int		x;
  int		y;
  char		button;
  char		click;
  eMouse	event;
}		t_mouse;

class Input
{
public:
  Input();
  ~Input();

  void	getInput(const Settings &set);
  bool	operator[](eAction act);
  bool	operator[](keyCode key);
  bool	operator[](t_mouse &key);

private:
  void	keyboardInput(const Settings &set, const SDL_Event &event, bool state);
  void	mouseInput(SDL_Event &event);
  std::vector<bool>		_actionState;
  std::map<keyCode, bool>	_boundKey;
  t_mouse			_mouse;
};

#endif /* _INPUT_H_ */
