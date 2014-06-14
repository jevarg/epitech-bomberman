#ifndef _LOADGAMEWIDGET_H_
# define _LOADGAMEWIDGET_H_

# include "LoadWidget.hpp"
# include "Menu.hpp"

class	LoadGameWidget : public LoadWidget
{
public:
  LoadGameWidget(int x, int y, int height, int width,
	     const std::string &texture, const std::string &text, int id);
  ~LoadGameWidget();

  void	onClick(t_gameinfo &gameInfo, Menu &menu);
};

#endif /* _LOADGAMEWIDGET_H_ */
