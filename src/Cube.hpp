<<<<<<< HEAD
#ifndef _CUBE_HPP_
# define _CUBE_HPP_

# include <iostream>
=======
 #ifndef _CUBE_HPP_
# define _CUBE_HPP_

>>>>>>> 35c0cf39dea90a7423e4e792261ed64446d55473
# include <glm/glm.hpp>
# include <glm/gtc/matrix_transform.hpp>
# include <Geometry.hh>
# include <Texture.hh>
# include <Clock.hh>
<<<<<<< HEAD
# include "IObject.hpp"
# include "Exception.hpp"
# include "Input.hpp"

class Input;
=======
# include <Input.hh>
# include <SDL_keycode.h>
# include <iostream>
# include "IObject.hpp"
# include "Exception.hpp"
>>>>>>> 35c0cf39dea90a7423e4e792261ed64446d55473

class Cube : public IObject
{
public:
  Cube();
  Cube(const std::string &);
  Cube(const Cube &);
  virtual ~Cube();
  virtual bool initialize();
<<<<<<< HEAD
=======
  virtual void update(gdl::Clock const &clock, gdl::Input &input);
>>>>>>> 35c0cf39dea90a7423e4e792261ed64446d55473
  virtual void draw(gdl::AShader &shader, gdl::Clock const &) const;
  virtual IObject *clone() const;
  void setTexture(gdl::Texture *texture);

private:
<<<<<<< HEAD

  gdl::Texture *_texture;
  gdl::Geometry *_geometry;
  std::string _file;
=======
  gdl::Texture *_texture;
  gdl::Geometry *_geometry;
  std::string _file;
  float _speed;
>>>>>>> 35c0cf39dea90a7423e4e792261ed64446d55473
};

#endif /* _CUBE_HPP_ */
