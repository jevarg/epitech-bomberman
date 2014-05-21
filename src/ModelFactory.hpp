#ifndef _MODELFACTORY_HPP_
# define _MODELFACTORY_HPP_

# include <string>
# include <vector>
# include <map>
# include <Texture.hh>
# include "Model.hpp"
# include "IObject.hpp"
# include "AEntity.hpp"
# include "Exception.hpp"

class ModelFactory
{
public:
  /* Appel */
  /* ModelFactory &fact = ModelFactory::getInstance(); */
  static ModelFactory &getInstance();
  void	addModel(eType, const std::string &);
  void	addModel(eType, IObject *, const std::string &);

  IObject	*getModel(eType type);

private:

  static ModelFactory _factory;

  ModelFactory();
  virtual ~ModelFactory();
  std::map<std::string, gdl::Texture*> _texture;
  std::map<eType, IObject *> _model;
};

#endif /* _MODELFACTORY_HPP_ */
