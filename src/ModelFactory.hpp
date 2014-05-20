#ifndef _MODELFACTORY_HPP_
#define _MODELFACTORY_HPP_

class ModelFactory
{
public:
  /* Appel */
  /* ModelFactory &fact = ModelFactory::getInstance(); */
  static const ModelFactory &getInstance();

private:

  static ModelFactory _factory;

  ModelFactory();
  virtual ~ModelFactory();

};

#endif /* _MODELFACTORY_HPP_ */
