#ifndef _INPUTWIDGET_H_
# define _INPUTWIDGET_H_

# include "LoadWidget.hpp"
# include "Menu.hpp"

class InputWidget : public LoadWidget
{
public:
  InputWidget(int x, int y, int height, int width,
	      const std::string &texture, const std::string &text, int id);
  ~InputWidget();

  void	onDisplay(const std::list<std::string> &text, int file);
  bool	isClicked(int x, int y);
  void	onClick(t_gameinfo &gameInfo, Menu &menu);
};

#endif /* _INPUTWIDGET_H_ */
