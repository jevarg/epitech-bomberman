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
      // Console	console(set);
      // std::string	ret;
      // console.parseCmd(std::string (av[1]), ret);
      // std::cout << "ret : " << ret << std::endl;
      // return (0);

      Menu menu;
      menu.launch();
    }
  catch (Exception &e)
    {
      std::cerr << e.what() << std::endl;
      return (1);
    }
  return (0);
}
