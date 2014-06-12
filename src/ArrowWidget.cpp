#include "ArrowWidget.hpp"

ArrowWidget::ArrowWidget(int x, int y, int height, int width,
			 const std::string &texture, int id)
  : AWidget(x, y, height, width)
{
  _square = new Square(texture);
  _square->initialize();
  _square->setPos(x, y);
  _square->setSize(width, height);
  _id = id;
}

ArrowWidget::~ArrowWidget()
{
}

void	ArrowWidget::onClick(t_gameinfo &gameInfo, Menu &menu)
{
  gameInfo.sound->play("click", EFFECT);
  if (_id == 0) //means Left
    --menu;
  else
    ++menu;
}

void	ArrowWidget::draw(gdl::AShader &shader, const gdl::Clock &clock)
{
  _square->fillGeometry();
  _square->draw(shader, clock);
}
