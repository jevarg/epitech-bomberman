#ifndef _INPUTWIDGET_H_
# define _INPUTWIDGET_H_

# include "AWidget.hpp"
# include "Menu.hpp"

class InputWidget : public AWidget
{
public:
  InputWidget(int x, int y, int height, int width, const std::string &text);
  ~InputWidget();

  void	onClick(const t_gameinfo &gameInfo, Menu &menu);
  void	draw(gdl::AShader &shader, const gdl::Clock &clock);
};

#endif /* _INPUTWIDGET_H_ */
