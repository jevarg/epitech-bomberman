#include "Cube.hpp"

Cube::Cube(): IObject(), _texture(NULL), _geometry(NULL), _file("")
{

}

Cube::Cube(const Cube &cpy)
  : IObject(), _texture(cpy._texture), _geometry(cpy._geometry), _file("")
{

}

Cube::Cube(const std::string &file): IObject(), _texture(NULL), _geometry(NULL), _file(file)
{

}

Cube::~Cube()
{
  // if (_texture)
  //   delete _texture;
  // if (_geometry)
  //   delete _geometry;
}

bool Cube::initialize()
{
  _geometry = new gdl::Geometry();

  if (!_texture)
    {
      _texture = new gdl::Texture();
      if (_file.size() && !_texture->load(_file))
	throw(Exception("Cannot load the texture"));
    }

  _geometry->pushVertex(glm::vec3(-1.0, -1.0, -1.0));
  _geometry->pushVertex(glm::vec3(1.0, -1.0, -1.0));
  _geometry->pushVertex(glm::vec3(1.0, 1.0, -1.0));
  _geometry->pushUv(glm::vec2(1.0 / 4.0, 1.0 / 3.0));
  _geometry->pushUv(glm::vec2(0.0f, 1.0 / 3.0));
  _geometry->pushUv(glm::vec2(0.0f, 2.0 / 3.0));

  _geometry->pushVertex(glm::vec3(-1.0, -1.0, -1.0));
  _geometry->pushVertex(glm::vec3(-1.0, 1.0, -1.0));
  _geometry->pushVertex(glm::vec3(1.0, 1.0, -1.0));
  _geometry->pushUv(glm::vec2(1.0 / 4.0, 1.0 / 3.0));
  _geometry->pushUv(glm::vec2(1.0 / 4.0, 2.0 / 3.0));
  _geometry->pushUv(glm::vec2(0.0f, 2.0 / 3.0));

  _geometry->pushVertex(glm::vec3(1.0, -1.0, 1.0));
  _geometry->pushVertex(glm::vec3(1.0, -1.0, -1.0));
  _geometry->pushVertex(glm::vec3(1.0, 1.0, -1.0));
  _geometry->pushUv(glm::vec2(3.0 / 4.0, 1.0 / 3.0));
  _geometry->pushUv(glm::vec2(1.0f, 1.0 / 3.0));
  _geometry->pushUv(glm::vec2(1.0f, 2.0 / 3.0));

  _geometry->pushVertex(glm::vec3(1.0, -1.0, 1.0));
  _geometry->pushVertex(glm::vec3(1.0, 1.0, 1.0));
  _geometry->pushVertex(glm::vec3(1.0, 1.0, -1.0));
  _geometry->pushUv(glm::vec2(3.0 / 4.0, 1.0 / 3.0));
  _geometry->pushUv(glm::vec2(3.0 / 4.0, 2.0 / 3.0));
  _geometry->pushUv(glm::vec2(1.0f, 2.0 / 3.0));

  _geometry->pushVertex(glm::vec3(-1.0, -1.0, 1.0));
  _geometry->pushVertex(glm::vec3(1.0, -1.0, 1.0));
  _geometry->pushVertex(glm::vec3(1.0, -1.0, -1.0));
  _geometry->pushUv(glm::vec2(2.0 / 4.0, 0.0f));
  _geometry->pushUv(glm::vec2(3.0 / 4.0, 0.0f));
  _geometry->pushUv(glm::vec2(3.0 / 4.0, 1.0 / 3.0));

  _geometry->pushVertex(glm::vec3(-1.0, -1.0, 1.0));
  _geometry->pushVertex(glm::vec3(-1.0, -1.0, -1.0));
  _geometry->pushVertex(glm::vec3(1.0, -1.0, -1.0));
  _geometry->pushUv(glm::vec2(2.0 / 4.0, 0.0f));
  _geometry->pushUv(glm::vec2(2.0 / 4.0, 1.0 / 3.0));
  _geometry->pushUv(glm::vec2(3.0 / 4.0, 1.0 / 3.0));

  _geometry->pushVertex(glm::vec3(-1.0, -1.0, 1.0));
  _geometry->pushVertex(glm::vec3(1.0, -1.0, 1.0));
  _geometry->pushVertex(glm::vec3(1.0, 1.0, 1.0));
  _geometry->pushUv(glm::vec2(2.0/4.0, 1.0 / 3.0));
  _geometry->pushUv(glm::vec2(3.0/4.0, 1.0 / 3.0));
  _geometry->pushUv(glm::vec2(3.0/4.0, 2.0 / 3.0));

  _geometry->pushVertex(glm::vec3(-1.0, -1.0, 1.0));
  _geometry->pushVertex(glm::vec3(-1.0, 1.0, 1.0));
  _geometry->pushVertex(glm::vec3(1.0, 1.0, 1.0));
  _geometry->pushUv(glm::vec2(2.0 / 4.0, 1.0 / 3.0));
  _geometry->pushUv(glm::vec2(2.0 / 4.0, 2.0 / 3.0));
  _geometry->pushUv(glm::vec2(3.0 / 4.0, 2.0 / 3.0));

  _geometry->pushVertex(glm::vec3(-1.0, -1.0, -1.0));
  _geometry->pushVertex(glm::vec3(-1.0, -1.0, 1.0));
  _geometry->pushVertex(glm::vec3(-1.0, 1.0, 1.0));
  _geometry->pushUv(glm::vec2(1.0 / 4.0, 1.0 / 3.0));
  _geometry->pushUv(glm::vec2(2.0 / 4.0, 1.0 / 3.0));
  _geometry->pushUv(glm::vec2(2.0 / 4.0, 2.0 / 3.0));

  _geometry->pushVertex(glm::vec3(-1.0, -1.0, -1.0));
  _geometry->pushVertex(glm::vec3(-1.0, 1.0, -1.0));
  _geometry->pushVertex(glm::vec3(-1.0, 1.0, 1.0));
  _geometry->pushUv(glm::vec2(1.0 / 4.0, 1.0 / 3.0));
  _geometry->pushUv(glm::vec2(1.0 / 4.0, 2.0 / 3.0));
  _geometry->pushUv(glm::vec2(2.0 / 4.0, 2.0 / 3.0));

  _geometry->pushVertex(glm::vec3(-1.0, 1.0, 1.0));
  _geometry->pushVertex(glm::vec3(1.0, 1.0, 1.0));
  _geometry->pushVertex(glm::vec3(1.0, 1.0, -1.0));
  _geometry->pushUv(glm::vec2(2.0 / 4.0, 2.0 / 3.0));
  _geometry->pushUv(glm::vec2(3.0 / 4.0, 2.0 / 3.0));
  _geometry->pushUv(glm::vec2(3.0 / 4.0, 3.0 / 3.0));

  _geometry->pushVertex(glm::vec3(-1.0, 1.0, 1.0));
  _geometry->pushVertex(glm::vec3(-1.0, 1.0, -1.0));
  _geometry->pushVertex(glm::vec3(1.0, 1.0, -1.0));
  _geometry->pushUv(glm::vec2(2.0 / 4.0, 2.0 / 3.0));
  _geometry->pushUv(glm::vec2(2.0 / 4.0, 3.0 / 3.0));
  _geometry->pushUv(glm::vec2(3.0 / 4.0, 3.0 / 3.0));

  _geometry->build();
  return (true);
}

void Cube::update(gdl::Clock const &, gdl::Input &)
{

}

void Cube::draw(gdl::AShader &shader, gdl::Clock const &) const
{
  if (_texture)
    _texture->bind();
  if (_geometry)
    _geometry->draw(shader, getTransformation(), GL_TRIANGLES);
}

IObject *Cube::clone() const
{
  return (new Cube(*this));
}

void Cube::setTexture(gdl::Texture *texture)
{
  _texture = texture;
}
