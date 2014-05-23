#ifndef CONSOLE_HPP_
# define CONSOLE_HPP_

# include <string>
# include <map>

# include "Settings.hpp"

class		Console
{
public:
  Console(Settings &set);
  ~Console();
  std::string	&parseCmd(const std::string &);

private:
  Settings	&_set;
  std::map<std::string, std::string &(Console::*)(const std::string &)> _cmd;
};

#endif /* !CONSOLE_HPP_ */
