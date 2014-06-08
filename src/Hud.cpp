#include "GameEngine.hpp"
#include "Hud.hpp"

HUD::HUD(gdl::AShader &shader)
  : _shader(shader), _heart(HEART_MODEL), _noHeart(NOHEART_MODEL), _fps()
{
  _heart.setSize(30, 30);
  _noHeart.setSize(30, 30);
  if (!_fps.initialize() || !_heart.initialize() || !_noHeart.initialize())
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
  _fps.draw(_shader, *gameInfo.clock);
  for (int i = HEALTH_MAX; i >= 1;i--)
    {
      if (i <= player->getHealth())
	{
	  _heart.setPos((3 - i) * 30, 0);
	  _heart.fillGeometry();
	  _heart.draw(_shader, *gameInfo.clock);
	}
      else
	{
	  _noHeart.setPos((3 - i) * 30, 0);
	  _noHeart.fillGeometry();
	  _noHeart.draw(_shader, *gameInfo.clock);
	}
    }
  glEnable(GL_DEPTH_TEST);
}
