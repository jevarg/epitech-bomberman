#ifndef SOUND_HPP_
# define SOUND_HPP_

# include <iostream>
# include <string>
# include <map>
# include <SDL2/SDL_mixer.h>

enum type
  {
    MUSIC,
    EFFECT
  };

class	Sound
{
public:
  Sound();
  ~Sound();
  bool	play(const std::string &, int type);

private:
  std::map<std::string, Mix_Music *>	_musicBox;
  std::map<std::string, Mix_Chunk *>	_soundBox;
};

#endif /* !SOUND_HPP */
