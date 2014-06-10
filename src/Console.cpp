#include <algorithm>
#include "Console.hpp"
#include "Settings.hpp"

# define POLICE_SIZE (30)

Console::Console(Settings &set, Input &input, gdl::Clock &clock, gdl::AShader &shader): _set(set), _input(input), _clock(clock), _shader(shader)
{
  _buf = "";
  _ret = "";
  _cmd["bind"] = &Console::bind;
  _cmd["set"] = &Console::set;
  _cmd["help"] = &Console::help;
  _cmd["import"] = &Console::import;
}

void	Console::print(Text &text, int winY)
{
  int	y = 0;

  for (int size = _toPrint.size(); size > (winY / POLICE_SIZE); --size)
    _toPrint.pop_back();
  for (std::list<std::string>::iterator it = _toPrint.begin(); it != _toPrint.end(); ++it)
    {
      text.setText(*it, 20, y * POLICE_SIZE, POLICE_SIZE);
      text.draw(_shader, _clock);
      ++y;
    }
}

bool	Console::aff(gdl::SdlContext const &win, float winX, float winY)
{
  Text		text;
  double	fps = 100.0;
  double	time;
  SDL_Keycode	key;

  if (text.initialize() == false)
    return (false);
  _toPrint.push_front(">");
  while (1)
    {
      _input.getInput(_set);
      _input[&key];
      win.updateClock(_clock);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      glDisable(GL_DEPTH_TEST);
      _shader.bind();
      _shader.setUniform("projection", glm::ortho(0.0f, 1600.0f, 900.0f, 0.0f, -1.0f, 1.0f));
      _shader.setUniform("view", glm::mat4(1));
      _shader.setUniform("winX", winX);
      _shader.setUniform("winY", winY);
      print(text, static_cast<int>(winY));
      glEnable(GL_DEPTH_TEST);
      win.flush();

      if (key == 27)
	return (true);
      if (key >= 1073741913 && key <= 1073741922)
	key = ((key - 1073741912) % 10) + '0';
      if (key == '\r' || key == 1073741912)
	{
	  if (_buf == "quit")
	    return (true);
	  parseCmd(_buf, _ret);
	  _ret = _buf + ":" + _ret;
	  _toPrint.front() = _ret;
	  _buf.clear();
	  _toPrint.push_front(">");
	}
      else if (key > 0 && key < 128)
	{
	  std::cout << "key != 0 : " << key << std::endl;
	  if (key == 8 && _buf.length() > 0)
	    _buf.erase(_buf.length() - 1, 1);
	  if (isPrintable(key) == true)
	    _buf.push_back(static_cast<char>(key));
	  if (_buf.empty() == true)
	    _toPrint.front()  = ">";
	  else
	    _toPrint.front() = _buf;
	}
      time = _clock.getElapsed();
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
      ret = arg + " : failed to bind " + arg + ".";
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
      ret = arg + " not enough arguments.";
      return (false);
    }
  tab[0] = "set";
  tab[1] = arg.substr(0, arg.find_first_of(' ', 0));
  tab[2] = arg.substr(arg.find_first_of(' ', 0) + 1, arg.length());
  if (_set.addCvar(tab) == false)
    {
      ret = arg + " failed to set " + arg + ".";
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
      ret = ": unknown command.";
      return (false);
    }
  if (nbr_space > 2)
    {
      ret = ": too many arguments.";
      return (false);
    }
  ptr = _cmd[cmd];
  return (this->*ptr)(arg, ret, nbr_space);
}

Console::~Console()
{
  ;
}
