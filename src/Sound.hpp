#ifndef SOUND_HPP_
# define SOUND_HPP_

# include <iostream>
# include <string>
# include <map>
# include <SDL2/SDL_mixer.h>

class	Sound
{
public:
  Sound();
  ~Sound();
  bool	playSound(const std::string &);
private:
  std::map<std::string, Mix_Music *>	_musicBox;
  std::map<std::string, Mix_Chunk *>	_soundBox;
};

#endif /* !SOUND_HPP */
