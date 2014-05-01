#include <iostream>
#include "GameEngine.hpp"
#include "Exception.hpp"


int	main(int ac, char **av)
{

  try
    {
      GameEngine eng;

      if (!eng.initialize())
	return (1);
      while (eng.update())
	eng.draw();
      return (0);
    }
  catch (Exception &e)
    {
      std::cerr << e.what() << std::endl;
    }
}
