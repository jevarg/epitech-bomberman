#ifndef _LOADWIDGET_H_
# define _LOADWIDGET_H_

# include "TextWidget.hpp"
# include "Menu.hpp"

class	LoadWidget : public TextWidget
{
public:
  LoadWidget(int x, int y, int height, int width,
	     const std::string &texture, const std::string &text, int id);
  ~LoadWidget();

  void	draw(gdl::AShader &shader, const gdl::Clock &clock);
  bool	isClicked(int x, int y);
  void	onDisplay(const std::list<std::string> &text, int filePos);
  virtual void	onClick(t_gameinfo &gameInfo, Menu &menu);

protected:
  std::string	_sentence;
  int		_id;
};

#endif /* _LOADWIDGET_H_ */
