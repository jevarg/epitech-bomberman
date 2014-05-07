
#include "Model.hpp"

Model::Model()
{
  _obj = NULL;
  _texture = NULL;
}

Model::~Model()
{
  if (_obj != NULL)
    delete _obj;
  if (_texture != NULL)
    delete _texture;
}

bool		Model::initialize()
{
  return (true);
}

void		Model::update(gdl::Clock const& clock, gdl::Input &input)
{

}

void		Model::draw(gdl::AShader &shader, gdl::Clock const& clock)
{
  if (_texture != NULL)
    _texture->bind();
  _obj->draw(shader, getTransformation(), GL_TRIANGLES);
}

bool		Model::load(std::string const& path)
{
  if (_obj != NULL)
    delete _obj;
  _obj = new gdl::Model();
  return (_obj->load(path));
}

bool		Model::loadTexture(std::string const& path)
{
  if (_texture != NULL)
    delete _texture;
  _texture = new gdl::Texture();
  return (_texture->load(path));
}
