#ifndef _NAVIGATIONWIDGET_HPP_
# define _NAVIGATIONWIDGET_HPP_

# include <vector>
# include "AWidget.hpp"

class	NavigationWidget : public AWidget
{
protected:
  std::vector<AWidget *>	*_onClickPanel;

public:
  NavigationWidget(int x, int y, int height, int width,
		   const std::string &text, std::vector<AWidget *> *onClickPanel);
  ~NavigationWidget();
  void	onClick(t_gameinfo &gameInfo, Menu &menu);
};

#endif
