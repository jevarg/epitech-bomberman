#ifndef _WIDGET_HPP_
# define _WIDGET_HPP_

# include <string>
# include "Text.hpp"

class	Widget
{
protected:
  Text		_text;
  int		_x;
  int		_y;
  int		_height;
  int		_width;

public:
  Widget(int x, int y, int height, int width, const std::string &text);
  ~Widget();

  void		onClick();
  void		display();

  int		getX() const;
  int		getY() const;
  int		getHeight() const;
  int		getWidth() const;
  const Text	&getText() const;  
};

#endif
