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
  void		update(gdl::Clock const&, gdl::Input &);
  void		draw(gdl::AShader &, gdl::Clock const&);
  bool		load(std::string const&);
  bool		loadTexture(std::string const&);
  IObject	*clone();

private:
  gdl::Model	*_obj;
  gdl::Texture	*_texture;
};

#endif /* _MODEL_H_ */
