#include "LoadWidget.hpp"

LoadWidget::LoadWidget(int x, int y, int height, int width,
		       const std::string &texture, const std::string &text, int id)
		       : TextWidget(x, y, height, width, text)
{
  _square = new Square(texture);
  _square->initialize();
  _square->setPos(x, y);
  _square->setSize(width, height);
  _sentence = text;
  _id = id;
}

LoadWidget::~LoadWidget()
{
}

void	LoadWidget::onDisplay(const std::list<std::string> &text, int filePos)
{
  std::list<std::string>::const_iterator it = text.begin();
  std::list<std::string>::const_iterator end = text.end();

  for (int count = 0; it != end; ++it, ++count)
    {
      if (count == _id + filePos * 4)
	{
	  _sentence = *it;
	  return ;
	}
    }
  _sentence = "FREE";
}

void	LoadWidget::onClick(t_gameinfo &gameInfo, Menu &/*menu*/)
{
  gameInfo.sound->play("click", EFFECT);
  gameInfo.map->load(_sentence, gameInfo);
}

void	LoadWidget::draw(gdl::AShader &shader, const gdl::Clock &clock)
{
  _square->fillGeometry();
  _square->draw(shader, clock);
  _text.setText(_sentence, _x + _width / 2 - (_sentence.length() / 4.0) * 45,
		_y + _height / 4, 45);
  glDisable(GL_DEPTH_TEST);
  _text.draw(shader, clock);
  glEnable(GL_DEPTH_TEST);
}
