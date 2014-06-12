#ifndef _NAVIGATIONWIDGET_HPP_
# define _NAVIGATIONWIDGET_HPP_

# include <vector>
# include "AWidget.hpp"
# include "Menu.hpp"

class	NavigationWidget : public AWidget
{
protected:
  std::vector<AWidget *>	*_onClickPanel;

public:
  NavigationWidget(int x, int y, int height, int width,
		   const std::string &texture, std::vector<AWidget *> *onClickPanel);
  ~NavigationWidget();

  void	draw(gdl::AShader &shader, const gdl::Clock &clock);
  void	onClick(t_gameinfo &gameInfo, Menu &menu);
};

#endif
