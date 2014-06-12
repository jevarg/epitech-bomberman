#include "KeyWidget.hpp"

KeyWidget::KeyWidget(int x, int y, int height, int width, eAction act) :
  InputWidget(x, y, height, width, "./assets/Button/button_small.tga", "")
{
  _act = act;
}

KeyWidget::~KeyWidget()
{
}

void	KeyWidget::init(const Settings * const set)
{
  std::vector<Keycode>	keySet;
  Keycode		key = 0;

  set->getKeyFromAct(_act, keySet);
  if (!keySet.empty())
    {
      if ((key = keySet.front()) > 0 && key < 128)
	{
	  _sentence.clear();
	  _sentence.push_back(static_cast<char>(key));
	}
    }
}

void	KeyWidget::onClick(t_gameinfo &gameInfo, Menu &menu)
{
  menu.textInput(_sentence, 2);
  if (_sentence.length() > 0)
    gameInfo.set->setKey(_sentence.at(0), _act);
}
