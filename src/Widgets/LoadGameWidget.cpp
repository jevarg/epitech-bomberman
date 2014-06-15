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
  gameInfo.sound->play("click", EFFECT);
  menu.launchGame(GAMES_PATH + _sentence, 1);
}
