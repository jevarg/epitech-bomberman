#ifndef _SETTINGS_H_
# define _SETTINGS_H_

# include <iostream>
# include <fstream>
# include <vector>
# include <map>

# define DEFAULT_FILE "default.cfg"

enum	eAction
  {
    UNKNOWN
  };

typedef unsigned char keyCode;

class Settings
{
public:
  Settings();
  ~Settings();

  void	loadFile(const std::string &);
private:
  void	readFile(std::vector<std::string> &inst, const std::string &);
  void	parsInst(const std::vector<std::string> &inst);

  std::map<keyCode, eAction>	_keyMap;
};

#endif /* _SETTINGS_H_ */
