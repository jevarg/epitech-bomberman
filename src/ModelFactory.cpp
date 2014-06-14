#include "ModelFactory.hpp"

ModelFactory ModelFactory::_factory = ModelFactory();

ModelFactory &ModelFactory::getInstance()
{
  return (_factory);
}

ModelFactory::ModelFactory(): _texture(), _model()
{

}


ModelFactory::~ModelFactory()
{
  for(std::map<std::string, gdl::Texture*>::iterator it= _texture.begin(); it != _texture.end(); it++)
    delete (it->second);
}

void	ModelFactory::addModel(eType type, const std::string &model_file)
{
  Model *model;

  if (_model[type] != NULL)
    delete _model[type];
  model = new Model();
  if (!model->load(model_file))
    throw(Exception("Cannot load Model"));
  _model[type] = model;
}

void	ModelFactory::addModel(eType type, IObject *obj, const std::string &texture_file)
{
  if (_model[type] != NULL)
    delete _model[type];
  _model[type] = obj;
  if (_texture[texture_file] == NULL)
    {
      _texture[texture_file] = new gdl::Texture();
      if (!_texture[texture_file]->load(texture_file))
	throw(Exception("Cannot load Texture"));
    }
  _model[type]->setTexture(_texture[texture_file]);
}

IObject	*ModelFactory::getModel(eType type)
{
  return (_model[type]->clone());
}
