#include <iostream>
<<<<<<< HEAD
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
  catch (const Exception &e)
=======
#include "GameEngine.hpp"
#include "Exception.hpp"
#include "Settings.hpp"
#include "Player.hpp"

int	main(int, char **)
{
  try
    {
      Settings	set;
      Input	input;

      set.loadFile(DEFAULT_FILE);
      GameEngine eng(set, input);

      if (!eng.initialize())
	return (1);
      while (eng.update())
	eng.draw();
      return (0);
    }
  catch (Exception &e)
>>>>>>> 35c0cf39dea90a7423e4e792261ed64446d55473
    {
      std::cerr << e.what() << std::endl;
      return (1);
    }
  return (0);
}
