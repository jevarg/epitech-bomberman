#ifndef _FULLSCREENWIDGET_H_
# define _FULLSCREENWIDGET_H_

# include "TextImgWidget.hpp"
# include "Menu.hpp"

class	FullScreenWidget : public TextImgWidget
{
public:
  FullScreenWidget(int x, int y, int height, int width,
	     const std::string &texture, const std::string &text);
  ~FullScreenWidget();

  void	init(const Settings * const set);
  bool	isClicked(int x, int y);
  void	onClick(t_gameinfo &gameInfo, Menu &menu);
};

#endif /* _FULLSCREENWIDGET_H_ */
