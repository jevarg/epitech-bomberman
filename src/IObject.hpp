#ifndef _IOBJECT_HPP_
# define _IOBJECT_HPP_

# include <Clock.hh>
<<<<<<< HEAD
# include <BasicShader.hh>
# include <Texture.hh>
# include "ATransformation.hpp"
# include "Input.hpp"
=======
# include <Input.hh>
# include <BasicShader.hh>
# include <Texture.hh>
# include "ATransformation.hpp"
>>>>>>> 35c0cf39dea90a7423e4e792261ed64446d55473

class IObject: public ATransformation
{
public:
  IObject(): ATransformation() {};
  virtual ~IObject() {};

  virtual bool initialize() = 0;
<<<<<<< HEAD
=======
  virtual void update(gdl::Clock const &, gdl::Input &) = 0;
>>>>>>> 35c0cf39dea90a7423e4e792261ed64446d55473
  virtual void draw(gdl::AShader &shader, gdl::Clock const &clock) const = 0;
  virtual IObject *clone() const = 0;
  virtual void setTexture(gdl::Texture *) = 0;
};

#endif /* _IOBJECT_HPP_ */
