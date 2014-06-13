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
  set->getKeyFromAct(_act, keySet);
  Keycode		key = 0;

  std::vector<Keycode>::const_iterator it = keySet.begin();
  std::vector<Keycode>::const_iterator end = keySet.end();

  for (; it != end; ++it)
    {
      if (*it > 0 && *it < 128)
	key = *it;
    }
  if (key != 0)
    {
      _sentence.clear();
      _sentence.push_back(static_cast<char>(key));
    }
}

void	KeyWidget::onClick(t_gameinfo &gameInfo, Menu &menu)
{
  menu.textInput(_sentence, 2);
  if (_sentence.length() > 0)
    gameInfo.set->setKey(_sentence.at(0), _act);
}
