#include "ClickTextWidget.hpp"

ClickTextWidget::ClickTextWidget(int x, int y, int height, int width,
				 const std::string &texture, const std::string &text) :
  TextImgWidget(x, y, height, width, texture, text)
{
}

ClickTextWidget::~ClickTextWidget()
{
}

bool	ClickTextWidget::isClicked(int x, int y)
{
  if (x >= _x && x <= (_x + _width) && y >= _y && y <= (_y + _height))
    return (true);
  else
    return (false);
}
