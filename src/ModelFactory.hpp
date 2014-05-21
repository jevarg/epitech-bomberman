#ifndef _MODELFACTORY_HPP_
# define _MODELFACTORY_HPP_

# include <string>
# include <vector>
# include <map>
# include <Texture.hh>
# include "Model.hpp"
# include "IObject.hpp"
# include "AEntity.hpp"

class ModelFactory
{
public:
  /* Appel */
  /* ModelFactory &fact = ModelFactory::getInstance(); */
  static const ModelFactory &getInstance();
  void	addModel(eType, IObject *);
  void	addModel(eType, const std::string &);
  void	addModel(eType, IObject *, const std::string &);
  void	addTexture(const std::string &);

  IObject	*getModel(eType type);

private:

  static ModelFactory _factory;

  ModelFactory();
  virtual ~ModelFactory();
  std::map<std::string, gdl::Texture*> _texture;
  std::map<eType, IObject *> _model;
};

#endif /* _MODELFACTORY_HPP_ */
