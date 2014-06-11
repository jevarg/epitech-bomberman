#ifndef _AWIDGET_HPP_
# define _AWIDGET_HPP_

# include <string>
# include "Text.hpp"
# include "GameEngine.hpp"
# include "Square.hpp"

class	Menu;

class	AWidget
{
protected:
  Text		_text;
  int		_x;
  int		_y;
  int		_height;
  int		_width;
  Square	*_square;

public:
  AWidget(int x, int y, int height, int width, const std::string &text);
  virtual ~AWidget() = 0;

  void		draw();

  bool		isClicked(int x, int y);
  virtual void	onClick(const t_gameinfo &gameInfo, Menu &menu) = 0;

  void		setSquare(Square *);
  Square	*getSquare() const;
  int		getX() const;
  int		getY() const;
  int		getHeight() const;
  int		getWidth() const;
  const Text	&getText() const;
};

#endif
