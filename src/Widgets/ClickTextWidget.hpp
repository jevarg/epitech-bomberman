#ifndef _CLICKTEXTWIDGET_H_
# define _CLICKTEXTWIDGET_H_

# include "TextImgWidget.hpp"
# include "Menu.hpp"

class	ClickTextWidget : public TextImgWidget
{
public:
  ClickTextWidget(int x, int y, int height, int width,
		const std::string &texture, const std::string &text);
  ~ClickTextWidget();

  bool	isClicked(int x, int y);
};

#endif /* _CLICKTEXTWIDGET_H_ */
