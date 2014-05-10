#ifndef _SETTINGS_H_
# define _SETTINGS_H_

# include <iostream>
# include <sstream>
# include <fstream>
# include <vector>
# include <map>

# define DEFAULT_FILE "default.cfg"

typedef std::vector<std::string>::const_iterator v_instCit;
typedef std::vector<std::string>::iterator v_instit;
typedef unsigned char keyCode;

enum	eAction
  {
    FORWARD = 0,
    BACK,
    LEFT,
    RIGHT,
    ACTIVATE,
    UNKNOWN
  };

/*
** /!\ Must be in the same order as the keywords are pushed in the vector
*/

enum	cvar
  {
    FPS = 0,
    FOV,
    WHEIGHT,
    WWIDTH
  };

class Settings
{
public:
  Settings();
  ~Settings();

  void	loadFile(const std::string &);
  int	toNumber(const std::string &);

private:
  bool	readFile(std::vector<std::string> &inst, const std::string &);
  void	parsInst(const std::vector<std::string> &inst);
  void	addKey(const std::string tab[3]);
  void	addCvar(const std::string tab[3]);

  std::vector<std::string>	_actionList;
  std::map<keyCode, eAction>	_keyMap;

  std::vector<std::string>     	_cvarList;
  std::map<cvar, int>		_cvarMap;
};

#endif /* _SETTINGS_H_ */
