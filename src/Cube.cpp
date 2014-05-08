#include "Cube.hpp"

Cube::Cube(): IObject()
{

}

Cube::Cube(const Cube &cpy): IObject(), _texture(cpy._texture), _geometry(cpy._geometry)
{

}

Cube::~Cube()
{

}

bool Cube::initialize()
{

  _geometry = new gdl::Geometry();
  _texture = new gdl::Texture();

  if (_texture->load("./assets/texture.tga") == false)
    {
      std::cerr << "Cannot load the cube texture" << std::endl;
      return (false);
    }

  _geometry->pushVertex(glm::vec3(-1.0, -1.0, -1.0));
  _geometry->pushVertex(glm::vec3(1.0, -1.0, -1.0));
  _geometry->pushVertex(glm::vec3(1.0, 1.0, -1.0));
  _geometry->pushUv(glm::vec2(0.0f, 0.0f));
  _geometry->pushUv(glm::vec2(1.0f, 0.0f));
  _geometry->pushUv(glm::vec2(1.0f, 1.0f));

  _geometry->pushVertex(glm::vec3(-1.0, -1.0, -1.0));
  _geometry->pushVertex(glm::vec3(-1.0, 1.0, -1.0));
  _geometry->pushVertex(glm::vec3(1.0, 1.0, -1.0));
  _geometry->pushUv(glm::vec2(0.0f, 0.0f));
  _geometry->pushUv(glm::vec2(0.0f, 1.0f));
  _geometry->pushUv(glm::vec2(1.0f, 1.0f));

  _geometry->pushVertex(glm::vec3(1.0, -1.0, 1.0));
  _geometry->pushVertex(glm::vec3(1.0, -1.0, -1.0));
  _geometry->pushVertex(glm::vec3(1.0, 1.0, -1.0));
  _geometry->pushUv(glm::vec2(0.0f, 0.0f));
  _geometry->pushUv(glm::vec2(1.0f, 0.0f));
  _geometry->pushUv(glm::vec2(1.0f, 1.0f));

  _geometry->pushVertex(glm::vec3(1.0, -1.0, 1.0));
  _geometry->pushVertex(glm::vec3(1.0, 1.0, 1.0));
  _geometry->pushVertex(glm::vec3(1.0, 1.0, -1.0));
  _geometry->pushUv(glm::vec2(0.0f, 0.0f));
  _geometry->pushUv(glm::vec2(0.0f, 1.0f));
  _geometry->pushUv(glm::vec2(1.0f, 1.0f));

  _geometry->pushVertex(glm::vec3(-1.0, -1.0, 1.0));
  _geometry->pushVertex(glm::vec3(1.0, -1.0, 1.0));
  _geometry->pushVertex(glm::vec3(1.0, -1.0, -1.0));
  _geometry->pushUv(glm::vec2(0.0f, 0.0f));
  _geometry->pushUv(glm::vec2(1.0f, 0.0f));
  _geometry->pushUv(glm::vec2(1.0f, 1.0f));

  _geometry->pushVertex(glm::vec3(-1.0, -1.0, 1.0));
  _geometry->pushVertex(glm::vec3(-1.0, -1.0, -1.0));
  _geometry->pushVertex(glm::vec3(1.0, -1.0, -1.0));
  _geometry->pushUv(glm::vec2(0.0f, 0.0f));
  _geometry->pushUv(glm::vec2(0.0f, 1.0f));
  _geometry->pushUv(glm::vec2(1.0f, 1.0f));

  _geometry->pushVertex(glm::vec3(-1.0, -1.0, 1.0));
  _geometry->pushVertex(glm::vec3(1.0, -1.0, 1.0));
  _geometry->pushVertex(glm::vec3(1.0, 1.0, 1.0));
  _geometry->pushUv(glm::vec2(0.0f, 0.0f));
  _geometry->pushUv(glm::vec2(1.0f, 0.0f));
  _geometry->pushUv(glm::vec2(1.0f, 1.0f));

  _geometry->pushVertex(glm::vec3(-1.0, -1.0, 1.0));
  _geometry->pushVertex(glm::vec3(-1.0, 1.0, 1.0));
  _geometry->pushVertex(glm::vec3(1.0, 1.0, 1.0));
  _geometry->pushUv(glm::vec2(0.0f, 0.0f));
  _geometry->pushUv(glm::vec2(0.0f, 1.0f));
  _geometry->pushUv(glm::vec2(1.0f, 1.0f));

  _geometry->pushVertex(glm::vec3(-1.0, -1.0, -1.0));
  _geometry->pushVertex(glm::vec3(-1.0, -1.0, 1.0));
  _geometry->pushVertex(glm::vec3(-1.0, 1.0, 1.0));
  _geometry->pushUv(glm::vec2(0.0f, 0.0f));
  _geometry->pushUv(glm::vec2(1.0f, 0.0f));
  _geometry->pushUv(glm::vec2(1.0f, 1.0f));

  _geometry->pushVertex(glm::vec3(-1.0, -1.0, -1.0));
  _geometry->pushVertex(glm::vec3(-1.0, 1.0, -1.0));
  _geometry->pushVertex(glm::vec3(-1.0, 1.0, 1.0));
  _geometry->pushUv(glm::vec2(0.0f, 0.0f));
  _geometry->pushUv(glm::vec2(0.0f, 1.0f));
  _geometry->pushUv(glm::vec2(1.0f, 1.0f));

  _geometry->pushVertex(glm::vec3(-1.0, 1.0, 1.0));
  _geometry->pushVertex(glm::vec3(1.0, 1.0, 1.0));
  _geometry->pushVertex(glm::vec3(1.0, 1.0, -1.0));
  _geometry->pushUv(glm::vec2(0.0f, 0.0f));
  _geometry->pushUv(glm::vec2(1.0f, 0.0f));
  _geometry->pushUv(glm::vec2(1.0f, 1.0f));

  _geometry->pushVertex(glm::vec3(-1.0, 1.0, 1.0));
  _geometry->pushVertex(glm::vec3(-1.0, 1.0, -1.0));
  _geometry->pushVertex(glm::vec3(1.0, 1.0, -1.0));
  _geometry->pushUv(glm::vec2(0.0f, 0.0f));
  _geometry->pushUv(glm::vec2(0.0f, 1.0f));
  _geometry->pushUv(glm::vec2(1.0f, 1.0f));

  _geometry->build();
  return (true);
}

void Cube::update(gdl::Clock const &, gdl::Input &)
{
}

void Cube::draw(gdl::AShader &shader, gdl::Clock const &)
{
  _texture->bind();
  _geometry->draw(shader, getTransformation(), GL_TRIANGLES);
}
