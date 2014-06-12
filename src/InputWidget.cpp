# include "InputWidget.hpp"

InputWidget::InputWidget(int x, int y, int height, int width,
			 const std::string &texture, const std::string &text, int id) :
  LoadWidget(x, y, height, width, texture, text, id)
{
}

InputWidget::~InputWidget()
{
}

void	InputWidget::onDisplay(const std::list<std::string> &/*text*/, int /*filePos*/)
{
}

bool	InputWidget::isClicked(int x, int y)
{
  if (x >= _x && x <= (_x + _width) && y >= _y && y <= (_y + _height))
    return (true);
  else
    return (false);
}

void	InputWidget::onClick(t_gameinfo &/*gameInfo*/, Menu &menu)
{
  menu.textInput(_sentence, 20);
  // here do a treatment with buf, buf contains the user's input.
}
