# include "InputWidget.hpp"

InputWidget::InputWidget(int x, int y, int height, int width,
		       const std::string &text) :
  AWidget(x, y, height, width)
{
}

InputWidget::~InputWidget()
{
}

void	InputWidget::onClick(const t_gameinfo &/*gameInfo*/, Menu &menu)
{
  std::string	buf;

  menu.textInput(buf, 20, _x, _y);
  // here do a treatment with buf, buf contains the user's input.
}

void	InputWidget::draw(gdl::AShader &shader, const gdl::Clock &clock)
{

}
