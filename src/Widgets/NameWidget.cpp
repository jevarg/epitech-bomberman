#include <sstream>
#include "NameWidget.hpp"

NameWidget::NameWidget(int x, int y, int height, int width,
		       const std::string &texture, int id) :
  InputWidget(x, y, height, width, texture, "")
{
  std::ostringstream oss;

  oss << id;
  _sentence = "Player " + oss.str();
  _id = id;
}

NameWidget::~NameWidget()
{
}

void	NameWidget::onClick(t_gameinfo &, Menu &menu)
{
  menu.textInput(_sentence, 20);
}
