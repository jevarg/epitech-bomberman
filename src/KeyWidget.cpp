#include "KeyWidget.hpp"

KeyWidget::KeyWidget(int x, int y, int height, int width) :
  InputWidget(x, y, height, width, "./assets/Button/button_small.tga", "")
{
}

KeyWidget::~KeyWidget()
{
}

void	KeyWidget::onClick(t_gameinfo &gameInfo, Menu &menu)
{
}
