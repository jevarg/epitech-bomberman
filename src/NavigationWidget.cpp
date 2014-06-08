#include "NavigationWidget.hpp"

NavigationWidget::NavigationWidget(int x, int y, int height, int width,
		   const std::string &text, std::vector<AWidget *> *onClickPanel)
  : AWidget(x, y, height, width, text)
{
  _onClickPanel = onClickPanel;
}

NavigationWidget::~NavigationWidget()
{
}

void	NavigationWidget::onClick(t_gameinfo &gameInfo, Menu &menu)
{
  menu._currentPanel = _onClickPanel;
}
