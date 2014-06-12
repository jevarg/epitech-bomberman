#include "NavigationWidget.hpp"

NavigationWidget::NavigationWidget(int x, int y, int height, int width,
		   const std::string &texture, std::vector<AWidget *> *onClickPanel)
  : AWidget(x, y, height, width, texture)
{
  _onClickPanel = onClickPanel;
  _square = new Square(texture);
  _square->initialize();
  _square->setPos(x, y);
  _square->setSize(width, height);
}

NavigationWidget::~NavigationWidget()
{
}

void	NavigationWidget::onClick(t_gameinfo &gameInfo, Menu &menu)
{
  menu.setCurrentPanel(_onClickPanel);
}

void	NavigationWidget::draw(gdl::AShader &shader, const gdl::Clock &clock)
{
  _square->fillGeometry();
  _square->draw(shader, clock);
}
