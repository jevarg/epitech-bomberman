#include "ModelFactory.hpp"

ModelFactory ModelFactory::_factory = ModelFactory();

const ModelFactory &ModelFactory::getInstance()
{
  return (_factory);
}

ModelFactory::ModelFactory()
{

}


ModelFactory::~ModelFactory()
{

}
