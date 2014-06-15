#include "FullScreenWidget.hpp"

FullScreenWidget::FullScreenWidget(int x, int y, int height, int width,
			       const std::string &texture, const std::string &text)
  : TextImgWidget(x, y, height, width, texture, text)
{
}

FullScreenWidget::~FullScreenWidget()
{
}

bool	FullScreenWidget::isClicked(int x, int y)
{
  if (x >= _x && x <= (_x + _width) && y >= _y && y <= (_y + _height))
    return (true);
  else
    return (false);
}

void	FullScreenWidget::init(const Settings * const set)
{
  int	val;

  try
    {
      val = set->getVar(R_FULLSCREEN);
    }
  catch (const Exception &e)
    {
      std::cerr << e.what() << std::endl;
      _sentence = "";
      return ;
    }
  if (val == 1)
    _sentence = "FullScreen On";
  else
    _sentence = "FullScreen Off";
}

void	FullScreenWidget::onClick(t_gameinfo &gameInfo, Menu &/*menu*/)
{
  gameInfo.set->setVar(R_FULLSCREEN, _sentence == "FullScreen Off");
  init(gameInfo.set);
  //  menu.setFullScreen(gameInfo.set);
}
