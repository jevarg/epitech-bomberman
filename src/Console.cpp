#include <algorithm>
#include "Console.hpp"
#include "Settings.hpp"

# define POLICE_SIZE (30)

Console::Console(Settings &set): _set(set)
{
  _cmd["bind"] = &Console::bind;
  _cmd["set"] = &Console::set;
  _cmd["help"] = &Console::help;
  _cmd["import"] = &Console::import;
}

bool	Console::aff(gdl::Clock &clock, gdl::AShader &shader, gdl::SdlContext const &win, Input input)
{
  double	fps = 100.0;
  double	time;
  Text		text;
  SDL_Keycode	key;

  _buf = "";
  _ret = "";
  if (text.initialize() == false)
    {
      std::cout << "returned false" << std::endl;
      return (false);
    }
  text.setText(">", 100, 600, POLICE_SIZE);
  while (1)
    {
      _oldBufLen = _buf.length();
      input.getInput(_set);
      input[&key];
      win.updateClock(clock);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      glDisable(GL_DEPTH_TEST);
      shader.bind();
      shader.setUniform("projection", glm::ortho(0.0f, 1600.0f, 900.0f, 0.0f, -1.0f, 1.0f));
      shader.setUniform("view", glm::mat4(1));
      text.draw(shader, clock);
      glEnable(GL_DEPTH_TEST);
      win.flush();
      if (key == 27)
	return (true);
      if (key >= 1073741913 && key <= 1073741922)
	key = ((key - 1073741912) % 10) + '0';
      if (key)
	printf("key : %d\n", key);
      if (key == '\r')
	{
	  if (_buf == "quit")
	    return (true);
	  parseCmd(_buf, _ret);
	  _buf.clear();
	  text.setText(_ret, 100, 600, POLICE_SIZE);
	}
      else if (key > 0 && key < 128)
	{
	  std::cout << "key != 0 : " << key << std::endl;
	  if (key == 8 && _buf.length() > 0)
	    _buf.erase(_buf.length() - 1, 1);
	  if (isPrintable(key) == true)
	    _buf.push_back(static_cast<char>(key));
	  if (_buf.empty() == true)
	    text.setText(">", 100, 600, POLICE_SIZE);
	  else
	    text.setText(_buf, 100, 600, POLICE_SIZE);
	  if (_buf.length() != _oldBufLen)
	    std::cout << "buf changed : " << _buf << std::endl;
	}
      time = clock.getElapsed();
      if (time < fps)
	usleep((fps - time) * 1000);
    }
  return (true);
}

bool	Console::isPrintable(char key)
{
  if (key >= ' ' && key <= '~')
    return (true);
  return (false);
}
	   
bool	Console::import(const std::string &arg, std::string &ret, int nbr_space)
{
  if (nbr_space == 1)
    {
      if (_set.loadFile(arg) == true)
	{
	  ret = "Successfully imported " + arg + ".";
	  return (true);
	}
      else
	{
	  ret = "Failed to import : " + arg;
	  return (false);
	}
    }
  ret = "Failed to import : " + arg + " : not enough arguments.";
  return (false);
}

bool	Console::bind(const std::string &arg, std::string &ret, int nbr_space)
{
  std::string	tab[3];

  if (nbr_space < 2)
    {
      ret = "bind " + arg + " : not enough arguments.";
      return (false);
    }
  tab[0] = "bind";
  tab[1] = arg.substr(0, arg.find_first_of(' ', 0));
  tab[2] = arg.substr(arg.find_first_of(' ', 0) + 1, arg.length());
  if (_set.addKey(tab) == false)
    {
      ret = "bind " + arg + " : failed to bind " + arg + ".";
      return (false);
    }
  ret = "Success.";
  return (true);
}

bool	Console::set(const std::string &arg, std::string &ret, int nbr_space)
{
  std::string	tab[3];

  if (nbr_space < 2)
    {
      ret = "set " + arg + " : not enough arguments.";
      return (false);
    }
  tab[0] = "set";
  tab[1] = arg.substr(0, arg.find_first_of(' ', 0));
  tab[2] = arg.substr(arg.find_first_of(' ', 0) + 1, arg.length());
  if (_set.addCvar(tab) == false)
    {
      ret = "set " + arg + " : failed to set " + arg + ".";
      return (false);
    }
  ret = "Success.";
  return (true);
}

bool	Console::help(const std::string &arg, std::string &ret, int nbr_space)
{
  (void)arg;
  (void)nbr_space;
  ret = "You can configure manually some features and options about the game.\n";
  ret += "You can bind a cvar using this syntax : \"bind cvar value\".\n";
  ret += "You can set a key using this syntax : \"set key action\".\n";
  ret += "You can import a config file using this syntax : \"import filename\".";
  std::cout << "outputting help" << std::endl;
  return (true);
}

bool	Console::parseCmd(const std::string &cmdline, std::string &ret)
{
  std::string	cmd;
  std::string	arg("");
  bool		(Console::*ptr)(const std::string &, std::string &, int);
  int		nbr_space = std::count(cmdline.begin(), cmdline.end(), ' ');

  if (nbr_space > 0)
    {
      cmd = cmdline.substr(0, cmdline.find_first_of(' ', 0));
      arg = cmdline.substr(cmdline.find_first_of(' ', 0) + 1, cmdline.length());
    }
  else
    cmd = cmdline;
  if (_cmd.find(cmd) == _cmd.end())
    {
      ret = cmd + ": unknown command.";
      return (false);
    }
  if (nbr_space > 2)
    {
      ret = cmd + ": too many arguments.";
      return (false);
    }
  ptr = _cmd[cmd];
  return (this->*ptr)(arg, ret, nbr_space);
}

Console::~Console()
{
  ;
}
