#include "SaveWidget.hpp"

SaveWidget::SaveWidget(int x, int y, int height, int width,
		       const std::string &texture, const std::string &text) :
  InputWidget(x, y, height, width, texture, text)
{
}

SaveWidget::~SaveWidget()
{
}

void	SaveWidget::init(const Settings * const /*set*/)
{
  _sentence = "Filename.game";
}

void	SaveWidget::onClick(t_gameinfo &gameInfo, Menu &menu)
{
  std::size_t	found;
  Save		saveobj;

  menu.textInput(_sentence, 20);
  found = _sentence.find(".game");
  if (found != std::string::npos && _sentence.size() > 5)
    try
      {
	saveobj.saveGame(*gameInfo.map, *gameInfo.set, GAMES_PATH + _sentence);
	_sentence = "Sucess";
      }
    catch(const Exception &e)
      {
	std::cerr << e.what() << std::endl;
	_sentence = "Error";
      }
  else
    _sentence = "Invalid: Filename.game";
}
