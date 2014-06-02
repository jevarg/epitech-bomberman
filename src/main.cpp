#include <iostream>
#include <string>
#include "GameEngine.hpp"
#include "Exception.hpp"
#include "Settings.hpp"
#include "Player.hpp"

int	main(int, char **av)
{
  try
    {
      Settings	set;
      set.loadFile(DEFAULT_FILE);
      set.loadFile(USER_FILE);

      // Console	console(set);
      // std::string	ret;
      // console.parseCmd(std::string (av[1]), ret);
      // std::cout << "ret : " << ret << std::endl;
      // return (0);

      Input	input;
      Map	map(set);
      gdl::Clock clock;
      Sound	sound;
      GameEngine eng(clock, map, set, input, sound);

      if (!eng.initialize())
	return (1);
      while (eng.update())
	eng.draw();
      return (0);
    }
  catch (Exception &e)
    {
      std::cerr << e.what() << std::endl;
      return (1);
    }
  return (0);
}
