#include "Widget.hpp"

Widget::Widget(int x, int y, int height, int width, const std::string &text)
  : _text()
{
  _x = x;
  _y = y;
  _height = height;
  _width = width;
  _text.setText(text, x + 3, y + 3, 50);
}

Widget::~Widget()
{
}


void	Widget::onClick()
{

}

void	Widget::display()
{

}

int	Widget::getX() const
{
  return (_x);
}

int	Widget::getY() const
{
  return (_y);
}

int	Widget::getHeight() const
{
  return (_height);
}

int	Widget::getWidth() const
{
  return (_width);
}

const Text	&Widget::getText() const
{
  return (_text);
}
