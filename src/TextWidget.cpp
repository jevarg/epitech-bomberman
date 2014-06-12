#include "TextWidget.hpp"

TextWidget::TextWidget(int x, int y, int height, int width, const std::string &text)
  : AWidget(x, y, height, width, text)
{

}

TextWidget::~TextWidget()
{

}

void	TextWidget::draw(gdl::AShader &shader, const gdl::Clock &clock)
{
  _text.draw(shader, clock);
}

bool	TextWidget::isClicked(int, int)
{
  return (false);
}

void	TextWidget::onClick(const t_gameinfo &, Menu &)
{
}

void	TextWidget::setText(std::string const& str, float x, float y, float size)
{
  _text.setText(str, x, y, size);
}
