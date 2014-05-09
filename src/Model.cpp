#include <iostream>
#include "Model.hpp"

Model::Model()
  : IObject()
{
  _obj = NULL;
  _texture = NULL;
}

Model::Model(Model const& model)
  : IObject(), _obj(model._obj), _texture(model._texture)
{

}

Model::~Model()
{
  if (_obj != NULL)
    delete _obj;
  if (_texture != NULL)
    delete _texture;
}

IObject *Model::clone() const
{
  return (new Model(*this));
}

bool		Model::initialize()
{
  return (true);
}

void		Model::update(gdl::Clock const& clock, gdl::Input &input)
{

}

void		Model::draw(gdl::AShader &shader, gdl::Clock const& clock) const
{
  if (_texture != NULL)
    {
      _texture->bind();
      std::cout << "TEXTURE" << std::endl;
    }
  _obj->draw(shader, getTransformation(), clock.getElapsed());
}

bool		Model::load(std::string const& path)
{
  if (_obj != NULL)
    delete _obj;
  _obj = new gdl::Model();
  if (!_obj->load(path))
    return (false);
  _obj->setCurrentAnim(0, false);
  return (true);
}

bool		Model::loadTexture(std::string const& path)
{
  if (_texture != NULL)
    delete _texture;
  _texture = new gdl::Texture();
  return (_texture->load(path));
}

void		Model::setTexture(gdl::Texture *texture)
{
  _texture = texture;
}
