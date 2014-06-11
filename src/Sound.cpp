#include "Sound.hpp"
#include "Exception.hpp"

Sound::Sound()
{
  try
    {
      if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
	throw (Exception("Mix_OpenAudio()"));
      Mix_AllocateChannels(128);
      _musicBox["intro"] = Mix_LoadMUS("./assets/sounds/calm1.ogg");
      _musicBox["menu"] = Mix_LoadMUS("./assets/sounds/calm2.ogg");
      _musicBox["game"] = Mix_LoadMUS("./assets/sounds/calm3.ogg");
      _soundBox["box"] = Mix_LoadWAV("./assets/sounds/chest.wav");
      _soundBox["creeper"] = Mix_LoadWAV("./assets/sounds/creeper.wav");
      _soundBox["eat"] = Mix_LoadWAV("./assets/sounds/eat.wav");
      _soundBox["explosion"] = Mix_LoadWAV("./assets/sounds/explosion.wav");
      _soundBox["fuse"] = Mix_LoadWAV("./assets/sounds/fuse.wav");
      _soundBox["hurt"] = Mix_LoadWAV("./assets/sounds/hurt.wav");
      _soundBox["pop"] = Mix_LoadWAV("./assets/sounds/pop.wav");
      _soundBox["orb"] = Mix_LoadWAV("./assets/sounds/orb.wav");
      _soundBox["click"] = Mix_LoadWAV("./assets/sounds/click.wav");
      _soundBox["getbomb"] = Mix_LoadWAV("./assets/sounds/getbomb.wav");
      _soundBox["burp"] = Mix_LoadWAV("./assets/sounds/burp.wav");
    }
  catch (Exception &e)
    {
      std::cerr << e.what() << std::endl;
      _musicBox["intro"] = NULL;
      _musicBox["menu"] = NULL;
      _musicBox["game"] = NULL;
      _soundBox["box"] = NULL;
      _soundBox["creeper"] = NULL;
      _soundBox["eat"] = NULL;
      _soundBox["explosion"] = NULL;
      _soundBox["fuse"] = NULL;
      _soundBox["hurt"] = NULL;
      _soundBox["pop"] = NULL;
      _soundBox["orb"] = NULL;
      _soundBox["click"] = NULL;
      _soundBox["getbomb"] = NULL;
      _soundBox["burp"] = NULL;
    }
}

Sound::~Sound()
{
  for (std::map<std::string, Mix_Music *>::iterator it = _musicBox.begin(); it != _musicBox.end(); ++it)
    if (it->second != NULL)
      Mix_FreeMusic(it->second);
  for (std::map<std::string, Mix_Chunk *>::iterator it = _soundBox.begin(); it != _soundBox.end(); ++it)
    if (it->second != NULL)
      Mix_FreeChunk(it->second);
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
