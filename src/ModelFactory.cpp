#include "ModelFactory.hpp"

ModelFactory ModelFactory::_factory = ModelFactory();

const ModelFactory &ModelFactory::getInstance()
{
  return (_factory);
}

ModelFactory::ModelFactory(): _texture(), _model()
{

}


ModelFactory::~ModelFactory()
{

}

void	ModelFactory::addModel(eType type, IObject *obj)
{

}

void	ModelFactory::addModel(eType type, const std::string &model_file)
{

}

void	ModelFactory::addModel(eType type, IObject *obj, const std::string &texture_file)
{

}

void	ModelFactory::addTexture(const std::string &texture_file)
{

}
