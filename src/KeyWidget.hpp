#ifndef _KEYWIDGET_H_
# define _KEYWIDGET_H_

# include "InputWidget.hpp"
# include "Menu.hpp"

class KeyWidget : public InputWidget
{
public:
  KeyWidget(int x, int y, int height, int width);
  ~KeyWidget();

  void	onClick(t_gameinfo &gameInfo, Menu &menu);
};

#endif /* _KEYWIDGET_H_ */
