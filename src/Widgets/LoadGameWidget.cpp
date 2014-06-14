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
  Save	saveobj;

  gameInfo.sound->play("click", EFFECT);
  try
    {
      saveobj.loadGame(GAMES_PATH + _sentence, gameInfo);
    }
  catch (const Exception &e)
    {
      std::cerr << e.what();
      return ;
    }
  menu.launchGame(GAMES_PATH + _sentence, true);
}
