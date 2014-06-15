#ifndef _ARROWWIDGET_H_
# define _ARROWWIDGET_H_

# include "AWidget.hpp"
# include "Menu.hpp"

class	ArrowWidget : public AWidget
{
public:
  ArrowWidget(int x, int y, int height, int width,
	      const std::string &texture, int id);
  ~ArrowWidget();

  void	draw(gdl::AShader &shader, const gdl::Clock &clock);
  void	onClick(t_gameinfo &gameInfo, Menu &menu);

private:
  int	_id;
};

#endif /* _ARROWWIDGET_H_ */
