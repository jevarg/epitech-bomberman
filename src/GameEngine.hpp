#ifndef _GAMEENGINE_HPP_
# define _GAMEENGINE_HPP_

# include <glm/glm.hpp>
# include <glm/gtc/matrix_transform.hpp>
# include <vector>
# include <unistd.h>
# include <Game.hh>
# include <BasicShader.hh>
# include <SdlContext.hh>
# include <Clock.hh>
# include <Input.hh>
# include "Cube.hpp"
# include "Exception.hpp"
# include "Camera.hpp"
# include "IObject.hpp"
# include "Model.hpp"
# include "AEntitie.hpp"
# include "Container.hpp"
# include "Map.hpp"

# define FPS 60.0f
# define FOV 60.0f
# define DEF_SIZE_X 800.0f
# define DEF_SIZE_Y 600.0f

# define WALL_TEXTURE "./assets/wall.tga"
# define SKY_TEXTURE "./assets/skybox.tga"
# define BOX_TEXTURE "./assets/box.tga"
# define GROUND_TEXTURE "./assets/ground.tga"

class GameEngine : public gdl::Game
{
public:
  GameEngine();
  ~GameEngine();

  virtual bool	initialize();
  virtual bool	update();
  virtual void	draw();
  float				_rotation;

private:
  void	createDisplayMap();

  gdl::SdlContext		_win;
  gdl::Input			_input;
  gdl::Clock			_clock;
  gdl::BasicShader		_shader;
  std::vector<IObject *>	_obj;
  Camera			_cam;
  int				_mapX;
  int				_mapY;
  Cube				_skybox;
  Model				_model;
  std::map<eType, IObject *>	_type;
  std::map<eType, gdl::Texture *>	_texture;
};

#endif /* _GAMEENGINE_HPP_ */
