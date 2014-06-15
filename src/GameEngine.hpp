#ifndef _GAMEENGINE_HPP_
# define _GAMEENGINE_HPP_

# include <glm/glm.hpp>
# include <glm/gtc/matrix_transform.hpp>
# include <vector>
<<<<<<< HEAD
# include <map>
# include <deque>
=======
>>>>>>> 35c0cf39dea90a7423e4e792261ed64446d55473
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
<<<<<<< HEAD
# include "Save.hpp"
# include "Container.hpp"
# include "AEntity.hpp"
# include "Map.hpp"
# include "Spawn.hpp"
# include "Settings.hpp"
# include "Input.hpp"
# include "Player.hpp"
# include "Text.hpp"
# include "Condvar.hpp"
# include "Mutex.hpp"
# include "Console.hpp"
# include "Scopelock.hpp"
# include "ModelFactory.hpp"
# include "EntityFactory.hpp"
# include "SpeedItem.hpp"
# include "HealthItem.hpp"
# include "StockItem.hpp"
# include "RangeItem.hpp"
# include "Text.hpp"
# include "Light.hpp"
# include "Sound.hpp"
# include "Flame.hpp"
# include "Bomb.hpp"
# include "Box.hpp"
# include "IA.hpp"
# include "Hud.hpp"
=======
# include "AEntitie.hpp"
# include "Save.hpp"
# include "Container.hpp"
# include "Map.hpp"
# include "Settings.hpp"
# include "Input.hpp"

# define CFPS 60.0f
# define CFOV 60.0f
# define DEF_SIZE_X 800.0f
# define DEF_SIZE_Y 600.0f
>>>>>>> 35c0cf39dea90a7423e4e792261ed64446d55473

# define WALL_TEXTURE "./assets/wall.tga"
# define SKY_TEXTURE "./assets/skybox.tga"
# define BOX_TEXTURE "./assets/box.tga"
<<<<<<< HEAD
# define FLAME_TEXTURE "./assets/flames.tga"
# define GROUND_TEXTURE "./assets/ground.tga"

# define WIN_TEXTURE "./assets/You-Win.tga"
# define LOSE_TEXTURE "./assets/You-Lose.tga"

# define HEALTHITEM_MODEL "./assets/health_item.fbx"
# define SPEEDITEM_MODEL "./assets/speed_item.fbx"
# define STOCKITEM_MODEL "./assets/stock_item.fbx"
# define RANGEITEM_MODEL "./assets/range_item.fbx"
# define CHARACTER_MODEL "./assets/steve.fbx"
# define CHARACTER2_MODEL "./assets/villager.fbx"
# define BOT_MODEL "./assets/pigman.fbx"
# define BOMB_MODEL "./assets/tnt.fbx"
# define CHICKEN_MODEL "./assets/chicken.fbx"

# define ABS(x) (((x) < 0) ? (-(x)) : (x))

typedef struct	s_gameinfo
{
  s_gameinfo(gdl::Clock *pclock, Map *pmap, Settings *pset, Input *pinput, Sound *psound, Save *psave) :
    clock(pclock), input(pinput), set(pset), sound(psound), map(pmap), save(psave)
  {
  }
  gdl::Clock   	*clock;
  Input	       	*input;
  Settings     	*set;
  Sound		*sound;
  Map	       	*map;
  Mutex		*mutex;
  Condvar	*condvar;
  Save		*save;
  std::map<std::string, int> score;
}		t_gameinfo;

class GameEngine : public gdl::Game
{
public:
  GameEngine(gdl::SdlContext *win, gdl::BasicShader *shader, t_gameinfo *gameInfo);
=======
# define GROUND_TEXTURE "./assets/ground.tga"

class GameEngine : public gdl::Game
{
public:
  GameEngine(Settings &set, Input &input);
>>>>>>> 35c0cf39dea90a7423e4e792261ed64446d55473
  ~GameEngine();

  virtual bool	initialize();
  virtual bool	update();
  virtual void	draw();

<<<<<<< HEAD
  void		setMulti(bool multi);
  void		setPlayer(Player *player1, Player *player2);
  void		setShutdown(bool shutdown);
  bool		loadMap(const std::string &file);
  void		resetAlreadyPlayed();
  void		setConsole(Console * const console);
  bool		isShutedDown() const;
  bool		loadSave(const std::string &file);
  bool		loadMap(const std::string &file, int ia);

private:
  void	mainInput();
  int	clearElements();
  void	displayScore();
  void	moveGround(Player *player, float mapX, float mapY);

  gdl::SdlContext		*_win;
  gdl::BasicShader		_shader;
  gdl::BasicShader		*_textShader;
  Cube				*_ground;
  Cube				*_skybox;
  Console			*_console;
  unsigned int			_mapX;
  unsigned int			_mapY;
  std::map<eType, IObject *>	_type;
  std::map<eType, gdl::Texture *>	_texture;
  Player			*_player;
  t_gameinfo			*_gameInfo;
  bool				_already_played;
  bool				_shutdown;
  int				_frames;
  std::vector<Light*>		_lights;
  Player			*_player1;
  Player			*_player2;
  std::vector<Player *>		_players;
  HUD				*_hud;
  Square			*_end_screen[2];
  std::map<std::string, int>	_score;
  Text				_fps;
  bool				_multi;
=======
private:
  void	createDisplayMap();
  void	createDisplayBorder();

  gdl::SdlContext		_win;
  gdl::Clock			_clock;
  gdl::BasicShader		_shader;
  Save				_save;
  std::vector<IObject *>	_obj;
  Camera			_cam;
  int				_mapX;
  int				_mapY;
  Cube				_skybox;
  Model				_model;
  Map				_map;
  Settings			&_set;
  Input				&_input;
  std::map<eType, IObject *>	_type;
  std::map<eType, gdl::Texture *>	_texture;
>>>>>>> 35c0cf39dea90a7423e4e792261ed64446d55473
};

#endif /* _GAMEENGINE_HPP_ */
