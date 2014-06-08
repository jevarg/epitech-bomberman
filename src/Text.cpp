#include <Clock.hh>
#include "Text.hpp"

Text::Text()
  : ATransformation()
{
  _geometry = NULL;
  _defX = 1500.0f;
  _defY = 800.0f;
  _defSize = 40.0f;
}

Text::~Text()
{
  if (_geometry)
    delete _geometry;
}

bool	Text::initialize()
{
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
      _geometry->draw(shader, getTransformation(), GL_TRIANGLES);
    }
}

void	Text::setText(std::string const& str, float x, float y, float size)
{
  float Letterx, Lettery;
  float	space = 0;

  if (_geometry)
    delete _geometry;
  _geometry = new gdl::Geometry();

  for (unsigned int i = 0; i < str.length(); ++i)
    {
      if (i > 0.5f)
	space = (i - (0.5f * i)) * size;
      Letterx = ((str[i] % 16) - 32 % 16) / 16.0f;
      Lettery = ((str[i] / 16) - 32 / 16) / 16.0f;

      _geometry->pushVertex(glm::vec3(x + space, y + size, 0));
      _geometry->pushVertex(glm::vec3(x + space + size, y + size, 0));
      _geometry->pushVertex(glm::vec3(x + space, y, 0));
      _geometry->pushUv(glm::vec2(Letterx, 1.0f - Lettery));
      _geometry->pushUv(glm::vec2(Letterx + 1.0f / 16.0f, 1.0f - Lettery));
      _geometry->pushUv(glm::vec2(Letterx, 1.0f - (Lettery + 1.0f / 16.0f)));

      _geometry->pushVertex(glm::vec3(x + space + size, y + size, 0));
      _geometry->pushVertex(glm::vec3(x + space, y, 0));
      _geometry->pushVertex(glm::vec3(x + space + size, y, 0));
      _geometry->pushUv(glm::vec2(Letterx + 1.0f / 16.0f, 1.0f - Lettery));
      _geometry->pushUv(glm::vec2(Letterx, 1.0f - (Lettery + 1.0f / 16.0f)));
      _geometry->pushUv(glm::vec2(Letterx + 1.0f / 16.0f, 1.0f - (Lettery + 1.0f / 16.0f)));
    }
  _geometry->build();
}
