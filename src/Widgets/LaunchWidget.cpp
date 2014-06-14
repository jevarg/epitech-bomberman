#include "LaunchWidget.hpp"

LaunchWidget::LaunchWidget(int x, int y, int height, int width,
			   const std::string &texture,
			   std::vector<AWidget *> *onClickPanel)
  : AWidget(x, y, height, width)
{
  _onClickPanel = onClickPanel;
  _square = new Square(texture);
  _square->initialize();
  _square->setPos(x, y);
  _square->setSize(width, height);
}

LaunchWidget::~LaunchWidget()
{
}

void	LaunchWidget::onClick(t_gameinfo &/*gameInfo*/, Menu &menu)
{
  menu.launchGame("", false);
  menu.setCurrentPanel(_onClickPanel);
}

void	LaunchWidget::draw(gdl::AShader &shader, const gdl::Clock &clock)
{
  _square->fillGeometry();
  _square->draw(shader, clock);
}
