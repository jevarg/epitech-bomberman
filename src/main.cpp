#include <iostream>
#include "Menu.hpp"
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
      Menu menu(set, input);

      menu.launch();
    }
  catch (Exception &e)
    {
      std::cerr << e.what() << std::endl;
      return (1);
    }
  return (0);
}
