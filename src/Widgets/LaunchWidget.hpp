#ifndef _LAUNCHWIDGET_HPP_
# define _LAUNCHWIDGET_HPP_

#include "AWidget.hpp"
#include "Menu.hpp"

class	LaunchWidget : public AWidget
{
private:
  std::vector<AWidget *>	*_onClickPanel;

public:
  LaunchWidget(int x, int y, int height, int width,
	       const std::string &texture, std::vector<AWidget *> *onClickPanel);
  ~LaunchWidget();

  virtual void	draw(gdl::AShader &shader, const gdl::Clock &clock);

  void	onClick(t_gameinfo &gameInfo, Menu &menu);
};

#endif
