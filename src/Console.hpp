#ifndef CONSOLE_HPP_
# define CONSOLE_HPP_

# include <string>
# include <map>

# include "Settings.hpp"
# include "GameEngine.hpp"

class		Console
{
public:
  Console(Settings &set);
  ~Console();
  bool		parseCmd(const std::string &, std::string &);
  bool		aff(gdl::Clock &clock, gdl::AShader &, gdl::SdlContext const&, Input);

private:
  bool		import(const std::string &, std::string &, int);
  bool		bind(const std::string &, std::string &, int);
  bool		set(const std::string &, std::string &, int);
  bool		help(const std::string &, std::string &, int);

  bool		isPrintable(char key);

  Settings	&_set;
  std::map<std::string, bool (Console::*)(const std::string &, std::string &, int)> _cmd;

  std::string	_buf;
  std::string	_ret;
  unsigned int	_oldBufLen;
};

#endif /* !CONSOLE_HPP_ */
