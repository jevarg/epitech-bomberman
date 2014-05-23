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
  bool		parseCmd(const std::string &, std::string &);

private:
  bool		bind(const std::string &, const std::string &, std::string &);
  bool		set(const std::string &, const std::string &, std::string &);
  bool		help(const std::string &, const std::string &, std::string &);

  Settings	&_set;
  std::map<std::string, bool (Console::*)(const std::string &, const std::string &, std::string &)> _cmd;
};

#endif /* !CONSOLE_HPP_ */
