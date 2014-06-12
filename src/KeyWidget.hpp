#ifndef _KEYWIDGET_H_
# define _KEYWIDGET_H_

# include "InputWidget.hpp"
# include "Menu.hpp"
# include "Settings.hpp"

class KeyWidget : public InputWidget
{
public:
  KeyWidget(int x, int y, int height, int width, eAction act);
  ~KeyWidget();

  void	onClick(t_gameinfo &gameInfo, Menu &menu);

private:
  eAction	_act;
};

#endif /* _KEYWIDGET_H_ */
