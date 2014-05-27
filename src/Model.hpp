#ifndef _MODEL_H_
# define _MODEL_H_

# include <Model.hh>
# include <Texture.hh>
# include <string>
# include "IObject.hpp"
# include "Exception.hpp"

class		Model: public IObject
{
public:
  Model();
  Model(Model const&);
  virtual ~Model();

  bool		initialize();
  bool		load(std::string const&);

  void		update(gdl::Clock const&, Input &);
  void		draw(gdl::AShader &, gdl::Clock const&) const;

  void		setTexture(gdl::Texture *);

  IObject	*clone() const;

  gdl::Model	*getModel();

private:
  gdl::Model	*_obj;
};

#endif /* !_MODEL_H_ */
