#ifndef _SAVEWIDGET_H_
# define _SAVEWIDGET_H_

# include "InputWidget.hpp"
# include "Menu.hpp"

class SaveWidget : public InputWidget
{
public:
  SaveWidget(int x, int y, int height, int width,
	     const std::string &texture, const std::string &text);
  ~SaveWidget();

  void	init(const Settings * const /*set*/);
  void	onClick(t_gameinfo &gameInfo, Menu &menu);
};

#endif /* _SAVEWIDGET_H_ */
