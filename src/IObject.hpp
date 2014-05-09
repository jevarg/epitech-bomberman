#ifndef _IOBJECT_HPP_
# define _IOBJECT_HPP_

# include <Clock.hh>
# include <Input.hh>
# include <BasicShader.hh>
# include "ATransformation.hpp"

class IObject: public ATransformation
{
public:
  IObject(): ATransformation() {};
  virtual ~IObject() {};

  virtual bool initialize() = 0;
  virtual void update(gdl::Clock const &, gdl::Input &) = 0;
  virtual void draw(gdl::AShader &shader, gdl::Clock const &clock) const = 0;
  virtual IObject *clone() const = 0;
  virtual void setTexture(gdl::Texture *) = 0;
};

#endif /* _IOBJECT_HPP_ */
