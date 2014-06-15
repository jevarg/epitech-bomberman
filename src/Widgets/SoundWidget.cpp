#include "SoundWidget.hpp"

SoundWidget::SoundWidget(int x, int y, int height, int width,
			       const std::string &texture, const std::string &text)
  : TextImgWidget(x, y, height, width, texture, text)
{
}

SoundWidget::~SoundWidget()
{
}

bool	SoundWidget::isClicked(int x, int y)
{
  if (x >= _x && x <= (_x + _width) && y >= _y && y <= (_y + _height))
    return (true);
  else
    return (false);
}

void	SoundWidget::init(const Settings * const set)
{
  int	val;

  try
    {
      val = set->getVar(S_MUTE);
    }
  catch (const Exception &e)
    {
      std::cerr << e.what() << std::endl;
      _sentence = "";
      return ;
    }
  if (val == 1)
    _sentence = "Sound Off";
  else
    _sentence = "Sound On";
}

void	SoundWidget::onClick(t_gameinfo &gameInfo, Menu &/*menu*/)
{
  gameInfo.set->setVar(S_MUTE, _sentence == "Sound On");
  gameInfo.sound->set(_sentence != "Sound On");
  init(gameInfo.set);
}
