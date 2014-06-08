#ifndef _HUD_HPP_
# define _HUD_HPP_

# include <BasicShader.hh>
# include "Player.hpp"
# include "Square.hpp"
# include "Text.hpp"

typedef struct s_gameinfo t_gameinfo;

# define HEART_MODEL "./assets/heart.tga"
# define NOHEART_MODEL "./assets/noheart.tga"

class HUD
{
public:
  HUD(gdl::AShader &shader);
  ~HUD();

  void setFps(float fps);
  void draw(Player *player, t_gameInfo &gameInfo);

private:
  gdl::AShader &_shader;
  Square _heart;
  Square _noHeart;
  Text	 _fps;
};

#endif /* _HUD_HPP_ */
