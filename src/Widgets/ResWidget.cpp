#include <sstream>
#include "ResWidget.hpp"

ResWidget::ResWidget(int x, int y, int height, int width,
			       const std::string &texture, const std::string &text)
  : TextImgWidget(x, y, height, width, texture, text)
{
}

ResWidget::~ResWidget()
{
}

bool	ResWidget::isClicked(int x, int y)
{
  if (x >= _x && x <= (_x + _width) && y >= _y && y <= (_y + _height))
    return (true);
  else
    return (false);
}

void	ResWidget::onClick(t_gameinfo &gameInfo, Menu &/*menu*/)
{
  std::string		tmp(_sentence);
  std::string		search("x");
  std::string		replace(" ");
  int		x;
  int		y;
  size_t	pos = 0;

  while ((pos = tmp.find(search, pos)) != std::string::npos)
    {
      tmp.replace(pos, search.length(), replace);
      pos += replace.length();
    }
  std::stringstream oss(tmp);
  oss >> x;
  oss >> y;
  std::cout << x << "x" << y << std::endl;
  gameInfo.sound->play("click", EFFECT);
  gameInfo.set->setVar(W_WIDTH, x);
  gameInfo.set->setVar(W_HEIGHT, y);
}
