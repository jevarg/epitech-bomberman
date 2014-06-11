#include "Sound.hpp"

Sound::Sound()
{
  try
    {
      if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
	throw (new std::string("Mix_OpenAudio()"));
      Mix_AllocateChannels(128);
      if ((_musicBox["intro"] = Mix_LoadMUS("./assets/sounds/calm1.ogg")) == NULL)
	std::cerr << "Failed to load intro music" << std::endl;
      if ((_musicBox["menu"] = Mix_LoadMUS("./assets/sounds/calm2.ogg")) == NULL)
	std::cerr << "Failed to load menu music" << std::endl;
      if ((_musicBox["game"] = Mix_LoadMUS("./assets/sounds/calm3.ogg")) == NULL)
	std::cerr << "Failed to load game music" << std::endl;
      
      if ((_soundBox["box"] = Mix_LoadWAV("./assets/sounds/chest.wav")) == NULL)
	std::cerr << "Failed to load box sound." << std::endl;
      if ((_soundBox["creeper"] = Mix_LoadWAV("./assets/sounds/creeper.wav")) == NULL)
	std::cerr << "Failed to load creeper sound." << std::endl;
      if ((_soundBox["eat"] = Mix_LoadWAV("./assets/sounds/eat.wav")) == NULL)
	std::cerr << "Failed to load eat sound." << std::endl;
      if ((_soundBox["explosion"] = Mix_LoadWAV("./assets/sounds/explosion.wav")) == NULL)
	std::cerr << "Failed to load use sound." << std::endl;
      if ((_soundBox["fuse"] = Mix_LoadWAV("./assets/sounds/fuse.wav")) == NULL)
	std::cerr << "Failed to load fuse sound." << std::endl;
      if ((_soundBox["hurt"] = Mix_LoadWAV("./assets/sounds/hurt.wav")) == NULL)
	std::cerr << "Failed to load hurt sound." << std::endl;
      if ((_soundBox["pop"] = Mix_LoadWAV("./assets/sounds/pop.wav")) == NULL)
	std::cerr << "Failed to load pop sound." << std::endl;
      if ((_soundBox["orb"] = Mix_LoadWAV("./assets/sounds/orb.wav")) == NULL)
	std::cerr << "Failed to load orb sound." << std::endl;
      if ((_soundBox["click"] = Mix_LoadWAV("./assets/sounds/orb.wav")) == NULL)
	std::cerr << "Failed to load click sound." << std::endl;
    }
  catch (std::string err)
    {
      std::cerr << "Sound initialization failed: " << err << std::endl;
      _soundBox["box"] = NULL;
      _soundBox["creeper"] = NULL;
      _soundBox["eat"] = NULL;
      _soundBox["explosion"] = NULL;
      _soundBox["fuse"] = NULL;
      _soundBox["hurt"] = NULL;
      _soundBox["pop"] = NULL;
      _soundBox["orb"] = NULL;
    }
}

Sound::~Sound()
{
  Mix_AllocateChannels(0);
  Mix_Quit();
}

bool	Sound::play(const std::string &to_play, int type)
{
  if (type == EFFECT)
    {
      if (_soundBox.find(to_play) != _soundBox.end())
	{
	  Mix_PlayChannel(-1, _soundBox[to_play], 0);
	  return (true);
	}
    }
  else if (type == MUSIC)
    {
      if (_musicBox.find(to_play) != _musicBox.end())
	{
	  Mix_PlayMusic(_musicBox[to_play], -1);
	  return (true);
	}
    }
  return (false);
}
