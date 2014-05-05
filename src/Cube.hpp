#ifndef _CUBE_HPP_
# define _CUBE_HPP_

# include <glm/glm.hpp>
# include <glm/gtc/matrix_transform.hpp>
# include <Geometry.hh>
# include <Texture.hh>
# include <Clock.hh>
# include <Input.hh>
# include <SDL_keycode.h>
# include <iostream>
# include "IObject.hpp"

class Cube : public IObject
{
public:
  Cube();
  Cube(const Cube &);
  virtual ~Cube();
  virtual bool initialize();
  virtual void update(gdl::Clock const &clock, gdl::Input &input);
  virtual void draw(gdl::AShader &shader, gdl::Clock const &);

private:
  gdl::Texture *_texture;
  gdl::Geometry *_geometry;
  float _speed;
};

#endif /* _CUBE_HPP_ */
