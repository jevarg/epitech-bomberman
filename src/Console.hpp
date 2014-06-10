#ifndef CONSOLE_HPP_
# define CONSOLE_HPP_

# include <string>
# include <map>
# include <list>

# include "Settings.hpp"
# include "GameEngine.hpp"

class		Console
{
public:
  Console(Settings &set, Input &input, gdl::Clock &clock, gdl::AShader &shader);
  ~Console();

  bool		parseCmd(const std::string &, std::string &);
  bool		aff(gdl::SdlContext const&, float x, float y);

private:
  bool		import(const std::string &, std::string &, int);
  bool		bind(const std::string &, std::string &, int);
  bool		set(const std::string &, std::string &, int);
  bool		help(const std::string &, std::string &, int);
  bool		isPrintable(char key);
  void		print(Text &text, int winY);

  Settings	&_set;
  Input		&_input;
  gdl::Clock	&_clock;
  gdl::AShader	&_shader;
  std::map<std::string, bool (Console::*)(const std::string &, std::string &, int)> _cmd;
  std::list<std::string>  _toPrint;
  std::string	_buf;
  std::string	_ret;
};

#endif /* !CONSOLE_HPP_ */
