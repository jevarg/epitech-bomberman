# include "TextWidget.hpp"

TextWidget::TextWidget(int x, int y, int height, int width,
		       const std::string &text) :
  AWidget(x, y, height, width, text)
{
  //  setSquare(new Square("assets/singleplayer.tga")); // tmp
}

TextWidget::~TextWidget()
{
}

void	TextWidget::onClick(const t_gameinfo &/*gameInfo*/, Menu &menu)
{
  std::string	buf;

  glDisable(GL_DEPTH_TEST);
  menu.textInput(buf, 20, _x, _y);
  // here do a treatment with buf, buf contains the user's input.
  glEnable(GL_DEPTH_TEST);
}
