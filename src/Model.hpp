#ifndef MODEL_HPP_
# define MODEL_HPP_

# include <Clock.hh>
# include <BasicShader.hh>
# include <glm/glm.hpp>

class	Model
{
public:
  Model();
  ~Model();
  void	draw(gdl::AShader &shader, gdl::Clock const &clock);
};

#endif /* !MODEL_HPP_ */
