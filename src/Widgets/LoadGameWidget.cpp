#include "LoadGameWidget.hpp"

LoadGameWidget::LoadGameWidget(int x, int y, int height, int width,
			       const std::string &texture, const std::string &text, int id)
  : LoadWidget(x, y, height, width, texture, text, id)
{
}

LoadGameWidget::~LoadGameWidget()
{
}

void	LoadGameWidget::onClick(t_gameinfo &gameInfo, Menu &menu)
{
  int	x = 0, y = 0;

  gameInfo.sound->play("click", EFFECT);
  gameInfo.map->determineMapSize(MAPS_PATH + _sentence, x, y);
  gameInfo.set->setVar(MAP_WIDTH, x);
  gameInfo.set->setVar(MAP_HEIGHT, y);
  gameInfo.map->load(MAPS_PATH + _sentence, gameInfo);
  menu.launchGame();
}
