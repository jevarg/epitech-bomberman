#include <iostream>
#include "Menu.hpp"
#include <string>
#include "GameEngine.hpp"
#include "Menu.hpp"
#include "Exception.hpp"
#include "Player.hpp"

int	main()
{
  int	seed;

  __asm__ volatile ("rdtsc" : "=A" (seed));
  std::srand(seed);
  try
    {
      Menu menu;
      menu.launch();
    }
  catch (const Exception &e)
    {
      std::cerr << e.what() << std::endl;
      return (1);
    }
  return (0);
}
