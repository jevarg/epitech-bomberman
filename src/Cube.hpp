#ifndef _CUBE_HPP_
# define _CUBE_HPP_

# include <iostream>
# include <glm/glm.hpp>
# include <glm/gtc/matrix_transform.hpp>
# include <Geometry.hh>
# include <Texture.hh>
# include <Clock.hh>
# include "IObject.hpp"
# include "Exception.hpp"

class Input;

class Cube : public IObject
{
public:
  Cube();
  Cube(const std::string &);
  Cube(const Cube &);
  virtual ~Cube();
  virtual bool initialize();
  virtual void update(gdl::Clock const &clock, Input &input);
  virtual void draw(gdl::AShader &shader, gdl::Clock const &) const;
  virtual IObject *clone() const;
  void setTexture(gdl::Texture *texture);

private:

  void pushVertex();
  void pushUv();
  void pushNormal();

  gdl::Texture *_texture;
  gdl::Geometry *_geometry;
  std::string _file;
  float _speed;
};

#endif /* _CUBE_HPP_ */
