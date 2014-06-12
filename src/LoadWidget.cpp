#include "LoadWidget.hpp"

LoadWidget::LoadWidget(int x, int y, int height, int width,
		       const std::string &texture, const std::string &text, int id)
  : TextImgWidget(x, y, height, width, texture, text)
{
  _id = id;
}

LoadWidget::~LoadWidget()
{
}

void	LoadWidget::onDisplay(const std::list<std::string> &text, int filePos)
{
  std::list<std::string>::const_iterator it = text.begin();
  std::list<std::string>::const_iterator end = text.end();

  std::cout << "Pass by here" << std::endl;
  for (int count = 0; it != end; ++it, ++count)
    {
      if (count == _id + filePos * 4)
	{
	  _sentence = *it;
	  return ;
	}
    }
  _sentence = "FREE";
}

bool	LoadWidget::isClicked(int x, int y)
{
  if (_sentence != "FREE" && x >= _x && x <= (_x + _width) && y >= _y && y <= (_y + _height))
    return (true);
  else
    return (false);
}

void	LoadWidget::onClick(t_gameinfo &gameInfo, Menu &menu)
{
  int	x = 0, y = 0;

  gameInfo.sound->play("click", EFFECT);
  gameInfo.map->determineMapSize(_sentence, x, y);
  gameInfo.set->setVar(MAP_WIDTH, x);
  gameInfo.set->setVar(MAP_HEIGHT, y);
  gameInfo.map->load(MAPS_PATH + _sentence, gameInfo);
  menu.launchGame();
}
