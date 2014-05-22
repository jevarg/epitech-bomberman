#include <iostream>
#include "GameEngine.hpp"
#include "Exception.hpp"
#include "Settings.hpp"
#include "Player.hpp"

int	main(int, char **)
{
  try
    {
      Settings	set;
      set.loadFile(DEFAULT_FILE);
      set.loadFile(USER_FILE);

      Input	input;
      Map	map(set);
      gdl::Clock clock;
      GameEngine eng(clock, map, set, input);

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
