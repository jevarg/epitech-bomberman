#ifndef _TEXT_H_
# define _TEXT_H_

# include <string>
# include <Texture.hh>
# include <Geometry.hh>
# include "ATransformation.hpp"

# define FONT "assets/font.tga"

class	Text: public ATransformation
{
public:
  Text();
  virtual ~Text();

  bool	initialize();
  void	clear();
  void	draw(gdl::AShader &, gdl::Clock const&) const;
  void	write(std::string const&, float, float, float);

private:
  gdl::Texture			_font;
  gdl::Geometry			*_geometry;
};

#endif /* _TEXT_H_ */
