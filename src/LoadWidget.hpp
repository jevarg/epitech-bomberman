#ifndef _LOADWIDGET_H_
# define _LOADWIDGET_H_

# include "TextWidget.hpp"
# include "Menu.hpp"

class	LoadWidget : public TextWidget
{
public:
  LoadWidget(int x, int y, int height, int width,
	     const std::string &texture, const std::string &text);
  ~LoadWidget();

  void	draw(gdl::AShader &shader, const gdl::Clock &clock);
  void	onClick(const t_gameinfo &gameInfo, Menu &menu);

private:
  std::string	_sentence;
};

#endif /* _LOADWIDGET_H_ */
