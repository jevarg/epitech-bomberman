#include <Clock.hh>
#include "Text.hpp"

Text::Text()
  : ATransformation()
{
  _geometry = NULL;
}

Text::~Text()
{
  if (_geometry)
    delete _geometry;
}

bool	Text::initialize()
{
  _geometry = new gdl::Geometry();
  return (_font.load(FONT));
}

void	Text::clear()
{
  if (_geometry)
    delete _geometry;
}

void	Text::draw(gdl::AShader &shader, gdl::Clock const&) const
{
  if (_geometry)
    {
      _font.bind();
      glDisable(GL_DEPTH_TEST);
      glAlphaFunc(GL_GREATER, 0.1f);
      glEnable(GL_ALPHA_TEST);
      _geometry->draw(shader, getTransformation(), GL_TRIANGLES);
      glDisable(GL_ALPHA_TEST);
      glEnable(GL_DEPTH_TEST);
    }
}

void	Text::write(std::string const& str, float x, float y, float size)
{
  float	UVx, UVy;
  if (_geometry)
    {
      for (unsigned int i = 0; i < str.length(); ++i)
	{
	  UVx = ((str[i] % 16) - 32 % 16) / 16.0f;
	  UVy = ((str[i] / 16) - 32 / 16)/ 16.0f;

	  _geometry->pushVertex(glm::vec3(x + i * size, y + size, 0)); // Top Left
	  _geometry->pushVertex(glm::vec3(x + i * size + size, y + size, 0)); // Top Right
	  _geometry->pushVertex(glm::vec3(x + i * size, y, 0)); // Bottom Left
	  _geometry->pushUv(glm::vec2(UVx, 1.0f - UVy));
	  _geometry->pushUv(glm::vec2(UVx + 1.0f / 16.0f, 1.0f - UVy));
	  _geometry->pushUv(glm::vec2(UVx, 1.0f - (UVy + 1.0f / 16.0f)));

	  _geometry->pushVertex(glm::vec3(x + i * size + size, y + size, 0)); // Top Right
	  _geometry->pushVertex(glm::vec3(x + i * size, y, 0)); // Bottom Left
	  _geometry->pushVertex(glm::vec3(x + i * size + size, y, 0)); // Bottom Right
	  _geometry->pushUv(glm::vec2(UVx + 1.0f / 16.0f, 1.0f - UVy));
	  _geometry->pushUv(glm::vec2(UVx, 1.0f - (UVy + 1.0f / 16.0f)));
	  _geometry->pushUv(glm::vec2(UVx + 1.0f / 16.0f, 1.0f - (UVy + 1.0f / 16.0f)));
	}
      _geometry->build();
    }
}
