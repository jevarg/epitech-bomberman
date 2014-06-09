#include "GameEngine.hpp"
#include "Hud.hpp"
HUD::HUD(gdl::AShader &shader)
  : _shader(shader), _stock(STOCK_TEXTURE), _nostock(NOSTOCK_TEXTURE),
    _heart(HEART_TEXTURE), _noHeart(NOHEART_TEXTURE), _fps()
{
  _stock.setSize(30, 30);
  _nostock.setSize(30, 30);
  _heart.setSize(30, 30);
  _noHeart.setSize(30, 30);
  if (!_fps.initialize() || !_heart.initialize() || !_noHeart.initialize()
      || !_stock.initialize() || !_nostock.initialize())
    throw(Exception("Cannot Init the HUD"));
}

HUD::~HUD()
{

}

void HUD::setFps(float fps)
{
  std::stringstream ss("");

  ss << fps;
  _fps.setText(ss.str(), 1500.0, 800.0, 50);
}

void HUD::draw(Player *player, t_gameinfo &gameInfo)
{
  float x = gameInfo.set->getVar(W_WIDTH), y = gameInfo.set->getVar(W_HEIGHT);

  glDisable(GL_DEPTH_TEST);
  _shader.bind();
  _shader.setUniform("projection", glm::ortho(0.0f, x, y, 0.0f, -1.0f, 1.0f));
  _shader.setUniform("view", glm::mat4(1));
  _shader.setUniform("winX", x);
  _shader.setUniform("winY", y);
  _fps.draw(_shader, *gameInfo.clock);
  for (int i = 1; i <= HEALTH_MAX;++i)
    {
      if (i <= player->getHealth())
	{
	  _heart.setPos(i * 30, 10);
	  _heart.fillGeometry();
	  _heart.draw(_shader, *gameInfo.clock);
	}
      else
	{
	  _noHeart.setPos(i * 30, 10);
	  _noHeart.fillGeometry();
	  _noHeart.draw(_shader, *gameInfo.clock);
	}
    }
  for (int i = 0;i < player->getMaxBomb();++i)
    {
      if (i < player->getBombStock())
  	{
  	  _stock.setPos((i + 1) * 30, 40);
  	  _stock.fillGeometry();
  	  _stock.draw(_shader, *gameInfo.clock);
  	}
      else
  	{
  	  _nostock.setPos((i + 1) * 30, 40);
  	  _nostock.fillGeometry();
  	  _nostock.draw(_shader, *gameInfo.clock);
  	}
    }
  glEnable(GL_DEPTH_TEST);
}
