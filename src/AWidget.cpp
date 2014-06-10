#include "AWidget.hpp"

AWidget::AWidget(int x, int y, int height, int width, const std::string &text)
  : _text()
{
  _x = x;
  _y = y;
  _height = height;
  _width = width;
  _text.setText(text, x + 3, y + 3, 50);
  _square = NULL;
}

AWidget::~AWidget()
{
}

void	AWidget::draw()
{

}

bool	AWidget::isClicked(int x, int y)
{
  if (x >= _x && x <= (_x + _width) && y >= _y && y <= (_y + _height))
    return (true);
  else
    return (false);
}

void	AWidget::setSquare(Square *square)
{
  _square = square;
}

Square	*AWidget::getSquare() const
{
  return (_square);
}

int	AWidget::getX() const
{
  return (_x);
}

int	AWidget::getY() const
{
  return (_y);
}

int	AWidget::getHeight() const
{
  return (_height);
}

int	AWidget::getWidth() const
{
  return (_width);
}

const Text	&AWidget::getText() const
{
  return (_text);
}
