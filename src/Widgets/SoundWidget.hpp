#ifndef _SOUNDWIDGET_H_
# define _SOUNDWIDGET_H_

# include "TextImgWidget.hpp"
# include "Menu.hpp"

class	SoundWidget : public TextImgWidget
{
public:
  SoundWidget(int x, int y, int height, int width,
	     const std::string &texture, const std::string &text);
  ~SoundWidget();

  void	init(const Settings * const set);
  bool	isClicked(int x, int y);
  void	onClick(t_gameinfo &gameInfo, Menu &menu);
};

#endif /* _SOUNDWIDGET_H_ */
