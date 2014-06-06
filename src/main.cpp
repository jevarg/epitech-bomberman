#include <iostream>
#include "Menu.hpp"
#include <string>
#include "GameEngine.hpp"
#include "Exception.hpp"
#include "Settings.hpp"
#include "Player.hpp"

int	main()
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

      Menu menu(set);

      menu.launch();
    }
  catch (Exception &e)
    {
      std::cerr << e.what() << std::endl;
      return (1);
    }
  return (0);
}
