#ifndef _NAMEWIDGET_H_
# define _NAMEWIDGET_H_

# include "InputWidget.hpp"
# include "Menu.hpp"
# include "Settings.hpp"

class NameWidget : public InputWidget
{
public:
  NameWidget(int x, int y, int height, int width,
	    const std::string &texture, int id);
  ~NameWidget();

  void	onClick(t_gameinfo &gameInfo, Menu &menu);
};

#endif /* _NAMEWIDGET_H_ */
