#include "Sound.hpp"

Sound::Sound()
{
  try
    {
      if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
	throw (new std::string("Mix_OpenAudio()"));
      Mix_AllocateChannels(4096);
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
    }
}

Sound::~Sound()
{
  Mix_Quit();
}

bool	Sound::playSound(const std::string &to_play)
{
  if (_soundBox.find(to_play) != _soundBox.end())
    {
      Mix_PlayChannel(-1, _soundBox[to_play], 0);
      return (true);
    }
  return (false);
}
