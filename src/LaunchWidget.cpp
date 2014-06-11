#include "LaunchWidget.hpp"

LaunchWidget::LaunchWidget(int x, int y, int height, int width, const std::string &texture)
  : AWidget(x, y, height, width, texture)
{
  _square = new Square(texture);
  _square->initialize();
  _square->setPos(x, y);
  _square->setSize(width, height);
}

LaunchWidget::~LaunchWidget()
{
}

void	LaunchWidget::onClick(const t_gameinfo &/*gameInfo*/, Menu &menu)
{
  menu.launchGame();
}

void	LaunchWidget::draw(gdl::AShader &shader, const gdl::Clock &clock)
{
  _square->fillGeometry();
  _square->draw(shader, clock);
}