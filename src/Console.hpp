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
  bool		aff();

private:
  bool		import(const std::string &, std::string &, int);
  bool		bind(const std::string &, std::string &, int);
  bool		set(const std::string &, std::string &, int);
  bool		help(const std::string &, std::string &, int);

  Settings	&_set;
  std::map<std::string, bool (Console::*)(const std::string &, std::string &, int)> _cmd;
};

#endif /* !CONSOLE_HPP_ */
