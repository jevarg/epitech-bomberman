#ifndef _SETTINGS_H_
# define _SETTINGS_H_

# include <iostream>
# include <sstream>
# include <fstream>
# include <vector>
# include <map>

# define DEFAULT_FILE "default.cfg"
# define UNBIND 0

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

  bool	cvarExist(cvar var) const;
  int	getVar(cvar var) const;
  void	setVar(cvar var, int value);
  eAction	getActionFromKey(keyCode key) const;
  int	getKeyFromAct(eAction act, std::vector<keyCode> &) const;
  void	setKey(keyCode key, eAction act);

  int	toNumber(const std::string &) const;

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
