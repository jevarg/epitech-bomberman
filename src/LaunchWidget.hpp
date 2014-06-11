#ifndef _LAUNCHWIDGET_HPP_
# define _LAUNCHWIDGET_HPP_

#include "AWidget.hpp"
#include "Menu.hpp"

class	LaunchWidget : public AWidget
{
public:
  LaunchWidget(int x, int y, int height, int width, const std::string &texture);
  ~LaunchWidget();

  virtual void	draw(gdl::AShader &shader, const gdl::Clock &clock);

  void	onClick(const t_gameinfo &gameInfo, Menu &menu);
};

#endif
