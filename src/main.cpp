#include <iostream>
#include "Menu.hpp"
#include "Exception.hpp"

int	main(int, char **)
{
  try
    {
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
