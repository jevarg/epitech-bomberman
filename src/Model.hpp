#ifndef _MODEL_H_
# define _MODEL_H_

# include <Model.hh>
# include <Texture.hh>
# include <string>
# include "IObject.hpp"
# include "Exception.hpp"
<<<<<<< HEAD
# include "Input.hpp"
=======
>>>>>>> 35c0cf39dea90a7423e4e792261ed64446d55473

class		Model: public IObject
{
public:
  Model();
  Model(Model const&);
  virtual ~Model();

  bool		initialize();
<<<<<<< HEAD
  bool		load(std::string const&);

  void		draw(gdl::AShader &, gdl::Clock const&) const;

  void		setTexture(gdl::Texture *);

  IObject	*clone() const;

  gdl::Model	*getModel();

private:
  gdl::Model	*_obj;
};

#endif /* !_MODEL_H_ */
=======
  void		update(gdl::Clock const&, gdl::Input &);
  void		draw(gdl::AShader &, gdl::Clock const&) const;
  bool		load(std::string const&);
  bool		loadTexture(std::string const&);
  IObject	*clone() const;
  void		setTexture(gdl::Texture *);

private:
  gdl::Model	*_obj;
  gdl::Texture	*_texture;
};

#endif /* _MODEL_H_ */
>>>>>>> 35c0cf39dea90a7423e4e792261ed64446d55473
