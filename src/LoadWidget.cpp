#include "LoadWidget.hpp"

LoadWidget::LoadWidget(int x, int y, int height, int width,
		       const std::string &texture, const std::string &text)
		       : TextWidget(x, y, height, width, text)
{
  _square = new Square(texture);
  _square->initialize();
  _square->setPos(x, y);
  _square->setSize(width, height);
  _sentence = text;
}

LoadWidget::~LoadWidget()
{
}

void	LoadWidget::onClick(const t_gameinfo &gameInfo, Menu &menu)
{
  gameInfo.sound->play("click", EFFECT);
}

void	LoadWidget::draw(gdl::AShader &shader, const gdl::Clock &clock)
{
  _square->fillGeometry();
  _square->draw(shader, clock);
  _text.setText(_sentence, _x + _width / 2 - (_sentence.length() / 4.0) * 45,
		_y + _height / 4, 45);
  glDisable(GL_DEPTH_TEST);
  _text.draw(shader, clock);
  glEnable(GL_DEPTH_TEST);
}
