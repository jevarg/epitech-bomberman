#ifndef _RESWIDGET_H_
# define _RESWIDGET_H_

# include "TextImgWidget.hpp"
# include "Menu.hpp"

class	ResWidget : public TextImgWidget
{
public:
  ResWidget(int x, int y, int height, int width,
	     const std::string &texture, const std::string &text);
  ~ResWidget();

  bool	isClicked(int x, int y);
  void	onClick(t_gameinfo &gameInfo, Menu &menu);
};

#endif /* _RESWIDGET_H_ */
