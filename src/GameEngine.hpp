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
# include "AEntitie.hpp"
# include "Map.hpp"

# define FPS 60.0f
# define FOV 60.0f
# define DEF_SIZE_X 800.0f
# define DEF_SIZE_Y 600.0f

class GameEngine : public gdl::Game
{
public:
  GameEngine();
  ~GameEngine();

  virtual bool	initialize();
  virtual bool	update();
  virtual void	draw();
private:
  gdl::SdlContext	_win;
  gdl::Input		_input;
  gdl::Clock		_clock;
  gdl::BasicShader		_shader;
  std::vector<AObject *>	_obj;
  Map			_map;
  Camera		_cam;
  int			_mapX;
  int			_mapY;
};

#endif /* _GAMEENGINE_HPP_ */
