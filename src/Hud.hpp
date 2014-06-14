#ifndef _HUD_HPP_
# define _HUD_HPP_

# include <BasicShader.hh>
# include "Player.hpp"
# include "Square.hpp"
# include "Text.hpp"

typedef struct s_gameinfo t_gameinfo;

# define STOCK_TEXTURE "./assets/stock.tga"
# define NOSTOCK_TEXTURE "./assets/nostock.tga"
# define HEART_TEXTURE "./assets/heart.tga"
# define NOHEART_TEXTURE "./assets/noheart.tga"

class HUD
{
public:
  HUD(gdl::AShader &shader);
  ~HUD();

  void setScore(float score, float x);
  void draw(Player *player, t_gameInfo &gameInfo, bool multi);

private:
  gdl::AShader &_shader;
  Square _stock;
  Square _nostock;
  Square _heart;
  Square _noHeart;
  Text	 _score;
};

#endif /* _HUD_HPP_ */
