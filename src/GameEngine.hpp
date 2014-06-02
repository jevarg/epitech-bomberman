#ifndef _GAMEENGINE_HPP_
# define _GAMEENGINE_HPP_

# include <glm/glm.hpp>
# include <glm/gtc/matrix_transform.hpp>
# include <vector>
# include <map>
# include <deque>
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
# include "Save.hpp"
# include "Container.hpp"
# include "AEntity.hpp"
# include "Map.hpp"
# include "Spawn.hpp"
# include "Settings.hpp"
# include "Input.hpp"
# include "Player.hpp"
# include "Condvar.hpp"
# include "Mutex.hpp"
# include "Console.hpp"
# include "Scopelock.hpp"
# include "ModelFactory.hpp"
# include "ItemFactory.hpp"
# include "SpeedItem.hpp"
# include "HealthItem.hpp"
# include "Text.hpp"
# include "Sound.hpp"

# define CFPS 60.0f
# define CFOV 60.0f
# define DEF_SIZE_X 1600.0f
# define DEF_SIZE_Y 900.0f

# define WALL_TEXTURE "./assets/wall.tga"
# define SKY_TEXTURE "./assets/skybox.tga"
# define BOX_TEXTURE "./assets/box.tga"
# define FLAME_TEXTURE "./assets/flames.tga"
# define GROUND_TEXTURE "./assets/ground.tga"
# define HEALTHITEM_MODEL "./assets/health_item.fbx"
# define SPEEDITEM_MODEL "./assets/speed_item.fbx"

# define CHARACTER_MODEL "./assets/steve.fbx"
# define BOMB_MODEL "./assets/tnt.fbx"

typedef struct	s_gameinfo
{
  s_gameinfo(gdl::Clock &pclock, Map &pmap, Settings &pset, Input &pinput, Sound &psound) :
    clock(pclock), map(pmap), input(pinput), set(pset), sound(psound)
  {
  }
  gdl::Clock   	&clock;
  Map	       	&map;
  Input	       	&input;
  Settings     	&set;
  Mutex		*mutex;
  Condvar	*condvar;
  Sound		&sound;
}		t_gameinfo;

class GameEngine : public gdl::Game
{
public:
  GameEngine(gdl::Clock &clock, Map &map, Settings &set, Input &input, Sound &sound);
  ~GameEngine();

  virtual bool	initialize();
  virtual bool	update();
  virtual void	draw();

private:
  void	createDisplayMap();
  void	createDisplayBorder();
  void	mainInput();
  int	clearElements();

  gdl::SdlContext		_win;
  gdl::BasicShader		_shader;
  Save				_save;
  std::vector<IObject *>	_obj;
  Camera			_cam;
  unsigned int			_mapX;
  unsigned int			_mapY;
  std::map<eType, IObject *>	_type;
  std::map<eType, gdl::Texture *>	_texture;
  Model				*_model;
  Player			*_player;
  t_gameinfo			_gameInfo;
  Text				_text;
  bool				_shutdown;
  int				_frames;
};

#endif /* _GAMEENGINE_HPP_ */
