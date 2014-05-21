#ifndef _GAMEENGINE_HPP_
# define _GAMEENGINE_HPP_

# include <glm/glm.hpp>
# include <glm/gtc/matrix_transform.hpp>
# include <vector>
# include <map>
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
# include "AEntity.hpp"
# include "Save.hpp"
# include "Container.hpp"
# include "Map.hpp"
# include "Spawn.hpp"
# include "Settings.hpp"
# include "Input.hpp"
# include "Player.hpp"
# include "Text.hpp"
# include "Condvar.hpp"
# include "Mutex.hpp"

# define CFPS 60.0f
# define CFOV 60.0f
# define DEF_SIZE_X 1600.0f
# define DEF_SIZE_Y 900.0f

# define WALL_TEXTURE "./assets/wall.tga"
# define SKY_TEXTURE "./assets/skybox.tga"
# define BOX_TEXTURE "./assets/box.tga"
# define GROUND_TEXTURE "./assets/ground.tga"
# define BOMB_TEXTURE "./assets/box.tga"
# define FLAME_TEXTURE "./assets/skybox.tga"

typedef struct	s_gameinfo
{
  s_gameinfo(gdl::Clock &pclock, Map &pmap, Settings &pset, Input &pinput) :
    clock(pclock), map(pmap), input(pinput), set(pset)
  {
  }
  gdl::Clock   	&clock;
  Map	       	&map;
  Input	       	&input;
  Settings     	&set;
  Mutex		*mutex;
  Condvar	*condvar;
}		t_gameinfo;

class GameEngine : public gdl::Game
{
public:
  GameEngine(gdl::SdlContext *win, gdl::Clock &clock, gdl::BasicShader *shader, Map &map,
	     Settings &set, Input &input);
  ~GameEngine();

  virtual bool	initialize();
  virtual bool	update();
  virtual void	draw();

private:
  void	createDisplayMap();
  void	createDisplayBorder();

  gdl::SdlContext		*_win;
  gdl::BasicShader		*_shader;
  Save				_save;
  std::vector<IObject *>	_obj;
  Camera			_cam;
  unsigned int			_mapX;
  unsigned int			_mapY;
  std::map<eType, IObject *>	_type;
  std::map<eType, gdl::Texture *>	_texture;
  Model				*_model;
  Player			*_player;
  Text				_text;
  t_gameinfo			_gameInfo;
};

#endif /* _GAMEENGINE_HPP_ */
