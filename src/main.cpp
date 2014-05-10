#include <iostream>
#include "GameEngine.hpp"
#include "Exception.hpp"
#include "Settings.hpp"
#include "Player.hpp"
#include "Map.hpp"

int	main(int, char **)
{
  try
    {
      GameEngine eng;
      Settings	set;

      set.loadFile(DEFAULT_FILE);
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
