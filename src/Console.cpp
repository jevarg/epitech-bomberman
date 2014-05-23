#include "Console.hpp"
#include "Settings.hpp"

Console::Console(Settings &set): _set(set)
{
  _cmd["bind"] = &Console::bind;
  _cmd["set"] = &Console::set;
  _cmd["help"] = &Console::help;
}

bool	Console::bind(const std::string &cmd, const std::string &arg, std::string &ret)
{
  (void)cmd;
  (void)ret;
  return (true);
}

bool	Console::set(const std::string &cmd, const std::string &arg, std::string &ret)
{
  (void)cmd;
  (void)ret;
  return (true);
}

bool	Console::help(const std::string &cmd, const std::string &arg, std::string &ret)
{
  (void)cmd;
  (void)ret;
  return (true);  
}

bool	Console::parseCmd(const std::string &cmdline, std::string &ret)
{
  std::string	cmd;
  std::string	arg;

  cmd = cmdline.substr(0, cmdline.find_first_of(' ', 0));
  std::cout << "cmd : " << cmd << std::endl;
  return (true);
}

Console::~Console()
{
  ;
}
