<<<<<<< HEAD
#include "Input.hpp"
=======
>>>>>>> 35c0cf39dea90a7423e4e792261ed64446d55473
#include "Cube.hpp"

Cube::Cube(): IObject(), _texture(NULL), _geometry(NULL), _file("")
{
<<<<<<< HEAD
=======

>>>>>>> 35c0cf39dea90a7423e4e792261ed64446d55473
}

Cube::Cube(const Cube &cpy)
  : IObject(), _texture(cpy._texture), _geometry(cpy._geometry), _file("")
{
<<<<<<< HEAD
=======

>>>>>>> 35c0cf39dea90a7423e4e792261ed64446d55473
}

Cube::Cube(const std::string &file): IObject(), _texture(NULL), _geometry(NULL), _file(file)
{
<<<<<<< HEAD
=======

>>>>>>> 35c0cf39dea90a7423e4e792261ed64446d55473
}

Cube::~Cube()
{
<<<<<<< HEAD
=======
  if (_texture)
    delete _texture;
  if (_geometry)
    delete _geometry;
>>>>>>> 35c0cf39dea90a7423e4e792261ed64446d55473
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

<<<<<<< HEAD
  _geometry->pushVertex(glm::vec3(-0.5, -0.5, -0.5));
  _geometry->pushVertex(glm::vec3(0.5, -0.5, -0.5));
  _geometry->pushVertex(glm::vec3(0.5, 0.5, -0.5));
  _geometry->pushUv(glm::vec2(1.0 / 4.0, 1.0 / 3.0));
  _geometry->pushUv(glm::vec2(0.0f, 1.0 / 3.0));
  _geometry->pushUv(glm::vec2(0.0f, 2.0 / 3.0));
  _geometry->pushNormal(glm::vec3(0.0, 0.0, -1.0));
  _geometry->pushNormal(glm::vec3(0.0, 0.0, -1.0));
  _geometry->pushNormal(glm::vec3(0.0, 0.0, -1.0));

  _geometry->pushVertex(glm::vec3(-0.5, -0.5, -0.5));
  _geometry->pushVertex(glm::vec3(-0.5, 0.5, -0.5));
  _geometry->pushVertex(glm::vec3(0.5, 0.5, -0.5));
  _geometry->pushUv(glm::vec2(1.0 / 4.0, 1.0 / 3.0));
  _geometry->pushUv(glm::vec2(1.0 / 4.0, 2.0 / 3.0));
  _geometry->pushUv(glm::vec2(0.0f, 2.0 / 3.0));
  _geometry->pushNormal(glm::vec3(0.0, 0.0, -1.0));
  _geometry->pushNormal(glm::vec3(0.0, 0.0, -1.0));
  _geometry->pushNormal(glm::vec3(0.0, 0.0, -1.0));

  _geometry->pushVertex(glm::vec3(0.5, -0.5, 0.5));
  _geometry->pushVertex(glm::vec3(0.5, -0.5, -0.5));
  _geometry->pushVertex(glm::vec3(0.5, 0.5, -0.5));
  _geometry->pushUv(glm::vec2(3.0 / 4.0, 1.0 / 3.0));
  _geometry->pushUv(glm::vec2(1.0f, 1.0 / 3.0));
  _geometry->pushUv(glm::vec2(1.0f, 2.0 / 3.0));
  _geometry->pushNormal(glm::vec3(1.0, 0.0, 0.0));
  _geometry->pushNormal(glm::vec3(1.0, 0.0, 0.0));
  _geometry->pushNormal(glm::vec3(1.0, 0.0, 0.0));

  _geometry->pushVertex(glm::vec3(0.5, -0.5, 0.5));
  _geometry->pushVertex(glm::vec3(0.5, 0.5, 0.5));
  _geometry->pushVertex(glm::vec3(0.5, 0.5, -0.5));
  _geometry->pushUv(glm::vec2(3.0 / 4.0, 1.0 / 3.0));
  _geometry->pushUv(glm::vec2(3.0 / 4.0, 2.0 / 3.0));
  _geometry->pushUv(glm::vec2(1.0f, 2.0 / 3.0));
  _geometry->pushNormal(glm::vec3(1.0, 0.0, 0.0));
  _geometry->pushNormal(glm::vec3(1.0, 0.0, 0.0));
  _geometry->pushNormal(glm::vec3(1.0, 0.0, 0.0));

  _geometry->pushVertex(glm::vec3(-0.5, -0.5, 0.5));
  _geometry->pushVertex(glm::vec3(0.5, -0.5, 0.5));
  _geometry->pushVertex(glm::vec3(0.5, -0.5, -0.5));
  _geometry->pushUv(glm::vec2(2.0 / 4.0, 0.0f));
  _geometry->pushUv(glm::vec2(3.0 / 4.0, 0.0f));
  _geometry->pushUv(glm::vec2(3.0 / 4.0, 1.0 / 3.0));
  _geometry->pushNormal(glm::vec3(0.0, -1.0, 0.0));
  _geometry->pushNormal(glm::vec3(0.0, -1.0, 0.0));
  _geometry->pushNormal(glm::vec3(0.0, -1.0, 0.0));

  _geometry->pushVertex(glm::vec3(-0.5, -0.5, 0.5));
  _geometry->pushVertex(glm::vec3(-0.5, -0.5, -0.5));
  _geometry->pushVertex(glm::vec3(0.5, -0.5, -0.5));
  _geometry->pushUv(glm::vec2(2.0 / 4.0, 0.0f));
  _geometry->pushUv(glm::vec2(2.0 / 4.0, 1.0 / 3.0));
  _geometry->pushUv(glm::vec2(3.0 / 4.0, 1.0 / 3.0));
  _geometry->pushNormal(glm::vec3(0.0, -1.0, 0.0));
  _geometry->pushNormal(glm::vec3(0.0, -1.0, 0.0));
  _geometry->pushNormal(glm::vec3(0.0, -1.0, 0.0));

  _geometry->pushVertex(glm::vec3(-0.5, -0.5, 0.5));
  _geometry->pushVertex(glm::vec3(0.5, -0.5, 0.5));
  _geometry->pushVertex(glm::vec3(0.5, 0.5, 0.5));
  _geometry->pushUv(glm::vec2(2.0/4.0, 1.0 / 3.0));
  _geometry->pushUv(glm::vec2(3.0/4.0, 1.0 / 3.0));
  _geometry->pushUv(glm::vec2(3.0/4.0, 2.0 / 3.0));
  _geometry->pushNormal(glm::vec3(0.0, 0.0, 1.0));
  _geometry->pushNormal(glm::vec3(0.0, 0.0, 1.0));
  _geometry->pushNormal(glm::vec3(0.0, 0.0, 1.0));

  _geometry->pushVertex(glm::vec3(-0.5, -0.5, 0.5));
  _geometry->pushVertex(glm::vec3(-0.5, 0.5, 0.5));
  _geometry->pushVertex(glm::vec3(0.5, 0.5, 0.5));
  _geometry->pushUv(glm::vec2(2.0 / 4.0, 1.0 / 3.0));
  _geometry->pushUv(glm::vec2(2.0 / 4.0, 2.0 / 3.0));
  _geometry->pushUv(glm::vec2(3.0 / 4.0, 2.0 / 3.0));
  _geometry->pushNormal(glm::vec3(0.0, 0.0, 1.0));
  _geometry->pushNormal(glm::vec3(0.0, 0.0, 1.0));
  _geometry->pushNormal(glm::vec3(0.0, 0.0, 1.0));

  _geometry->pushVertex(glm::vec3(-0.5, -0.5, -0.5));
  _geometry->pushVertex(glm::vec3(-0.5, -0.5, 0.5));
  _geometry->pushVertex(glm::vec3(-0.5, 0.5, 0.5));
  _geometry->pushUv(glm::vec2(1.0 / 4.0, 1.0 / 3.0));
  _geometry->pushUv(glm::vec2(2.0 / 4.0, 1.0 / 3.0));
  _geometry->pushUv(glm::vec2(2.0 / 4.0, 2.0 / 3.0));
  _geometry->pushNormal(glm::vec3(-1.0, 0.0, 0.0));
  _geometry->pushNormal(glm::vec3(-1.0, 0.0, 0.0));
  _geometry->pushNormal(glm::vec3(-1.0, 0.0, 0.0));

  _geometry->pushVertex(glm::vec3(-0.5, -0.5, -0.5));
  _geometry->pushVertex(glm::vec3(-0.5, 0.5, -0.5));
  _geometry->pushVertex(glm::vec3(-0.5, 0.5, 0.5));
  _geometry->pushUv(glm::vec2(1.0 / 4.0, 1.0 / 3.0));
  _geometry->pushUv(glm::vec2(1.0 / 4.0, 2.0 / 3.0));
  _geometry->pushUv(glm::vec2(2.0 / 4.0, 2.0 / 3.0));
  _geometry->pushNormal(glm::vec3(-1.0, 0.0, 0.0));
  _geometry->pushNormal(glm::vec3(-1.0, 0.0, 0.0));
  _geometry->pushNormal(glm::vec3(-1.0, 0.0, 0.0));

  _geometry->pushVertex(glm::vec3(-0.5, 0.5, 0.5));
  _geometry->pushVertex(glm::vec3(0.5, 0.5, 0.5));
  _geometry->pushVertex(glm::vec3(0.5, 0.5, -0.5));
  _geometry->pushUv(glm::vec2(2.0 / 4.0, 2.0 / 3.0));
  _geometry->pushUv(glm::vec2(3.0 / 4.0, 2.0 / 3.0));
  _geometry->pushUv(glm::vec2(3.0 / 4.0, 3.0 / 3.0));
  _geometry->pushNormal(glm::vec3(0.0, 1.0, 0.0));
  _geometry->pushNormal(glm::vec3(0.0, 1.0, 0.0));
  _geometry->pushNormal(glm::vec3(0.0, 1.0, 0.0));

  _geometry->pushVertex(glm::vec3(-0.5, 0.5, 0.5));
  _geometry->pushVertex(glm::vec3(-0.5, 0.5, -0.5));
  _geometry->pushVertex(glm::vec3(0.5, 0.5, -0.5));
  _geometry->pushUv(glm::vec2(2.0 / 4.0, 2.0 / 3.0));
  _geometry->pushUv(glm::vec2(2.0 / 4.0, 3.0 / 3.0));
  _geometry->pushUv(glm::vec2(3.0 / 4.0, 3.0 / 3.0));
  _geometry->pushNormal(glm::vec3(0.0, 1.0, 0.0));
  _geometry->pushNormal(glm::vec3(0.0, 1.0, 0.0));
  _geometry->pushNormal(glm::vec3(0.0, 1.0, 0.0));
=======
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
>>>>>>> 35c0cf39dea90a7423e4e792261ed64446d55473

  _geometry->build();
  return (true);
}

<<<<<<< HEAD
=======
void Cube::update(gdl::Clock const &, gdl::Input &)
{

}

>>>>>>> 35c0cf39dea90a7423e4e792261ed64446d55473
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
