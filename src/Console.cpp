#include <algorithm>
#include "Console.hpp"
#include "Settings.hpp"

Console::Console(Settings &set): _set(set)
{
  _cmd["bind"] = &Console::bind;
  _cmd["set"] = &Console::set;
  _cmd["help"] = &Console::help;
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
  tab[2] = arg.substr(arg.find_first_of(' ', 0), arg.length());
  return (_set.addKey(tab));
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
  tab[2] = arg.substr(arg.find_first_of(' ', 0), arg.length());
  return (_set.addCvar(tab));
}

bool	Console::help(const std::string &arg, std::string &ret, int nbr_space)
{
  (void)ret;
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
