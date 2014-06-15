#include "Model.hpp"

Model::Model()
  : IObject()
{
  _obj = NULL;
<<<<<<< HEAD
}

Model::Model(Model const& model)
  : IObject(), _obj(model._obj)
{
=======
  _texture = NULL;
}

Model::Model(Model const& model)
  : IObject(), _obj(model._obj), _texture(model._texture)
{

>>>>>>> 35c0cf39dea90a7423e4e792261ed64446d55473
}

Model::~Model()
{
  if (_obj != NULL)
    delete _obj;
<<<<<<< HEAD
=======
  if (_texture != NULL)
    delete _texture;
>>>>>>> 35c0cf39dea90a7423e4e792261ed64446d55473
}

IObject *Model::clone() const
{
  return (new Model(*this));
}

bool		Model::initialize()
{
  return (true);
}

<<<<<<< HEAD
void	Model::draw(gdl::AShader &shader, gdl::Clock const& clock) const
{
=======
void		Model::update(gdl::Clock const& clock, gdl::Input &input)
{

}

void		Model::draw(gdl::AShader &shader, gdl::Clock const& clock) const
{
  if (_texture != NULL)
    _texture->bind();
>>>>>>> 35c0cf39dea90a7423e4e792261ed64446d55473
  _obj->draw(shader, getTransformation(), clock.getElapsed());
}

bool		Model::load(std::string const& path)
{
  if (_obj != NULL)
    delete _obj;
  _obj = new gdl::Model();
  if (!_obj->load(path))
    return (false);
<<<<<<< HEAD
  _obj->setCurrentAnim(0, true);
  return (true);
}

void		Model::setTexture(gdl::Texture *)
{
}

gdl::Model	*Model::getModel()
{
  return (_obj);
=======
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
>>>>>>> 35c0cf39dea90a7423e4e792261ed64446d55473
}
