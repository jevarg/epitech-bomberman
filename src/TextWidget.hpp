#ifndef _TEXTWIDGET_H_
# define _TEXTWIDGET_H_

# include "AWidget.hpp"
# include "Menu.hpp"

class TextWidget : public AWidget
{
public:
  TextWidget(int x, int y, int height, int width, const std::string &text);
  ~TextWidget();

  void	onClick(const t_gameinfo &gameInfo, Menu &menu);
};

#endif /* _TEXTWIDGET_H_ */
