#ifndef _GAMEENGINE_HPP_
# define _GAMEENGINE_HPP_

# include <unistd.h>
# include <Game.hh>
# include <SdlContext.hh>
# include <Clock.hh>
# include <Input.hh>

# define FPS 60

class GameEngine : public gdl::Game
{
public:
  ~GameEngine();

  virtual bool initialize();
  virtual bool update();
  virtual void draw();

private:
  gdl::SdlContext _win;
  gdl::Input	  _input;
  gdl::Clock	  _clock;
};

#endif /* _GAMEENGINE_HPP_ */
