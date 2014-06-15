#ifndef _SETTINGS_H_
# define _SETTINGS_H_

<<<<<<< HEAD
# include <SDL.h>
# include <string>
=======
>>>>>>> 35c0cf39dea90a7423e4e792261ed64446d55473
# include <iostream>
# include <sstream>
# include <fstream>
# include <vector>
# include <map>
<<<<<<< HEAD
# include "Exception.hpp"

# define DEFAULT_FILE "default.cfg"
# define USER_FILE "config.cfg"
# define UNBIND 0
# define UNKNOWN_KEY -1
# define POLICE_SIZE 30

typedef	struct	s_cvar	t_cvar;

typedef int Keycode;
typedef std::vector<std::string>::const_iterator v_instCit;
typedef std::vector<std::string>::iterator v_instit;
typedef std::vector<t_cvar *>::iterator v_cvarit;
typedef std::map<std::string, Keycode>::const_iterator m_keyCit;
=======

# define DEFAULT_FILE "default.cfg"
# define UNBIND 0

typedef std::vector<std::string>::const_iterator v_instCit;
typedef std::vector<std::string>::iterator v_instit;
typedef int keyCode;
>>>>>>> 35c0cf39dea90a7423e4e792261ed64446d55473

enum	eAction
  {
    FORWARD = 0,
    BACK,
    LEFT,
    RIGHT,
<<<<<<< HEAD
    DROPBOMB,
    ACTIVATE,
    LAUNCHGAME,
=======
    ACTIVATE,
>>>>>>> 35c0cf39dea90a7423e4e792261ed64446d55473
    UNKNOWN
  };

/*
** /!\ Must be in the same order as the keywords are pushed in the vector
*/

enum	cvar
  {
    FPS = 0,
    FOV,
    W_HEIGHT,
    W_WIDTH,
<<<<<<< HEAD
    MAP_HEIGHT,
    MAP_WIDTH,
    MAP_DENSITY,
    MAP_LINEAR,
    R_FULLSCREEN,
    R_MIPMAP,
    FIRESPEED,
    FIRETIME,
    R_DEPTHVIEW,
    R_DRAWFOG,
    R_SKYBOX
  };

typedef	struct	s_cvar
{
  s_cvar(const std::string &pname, int pmin_value, int pmax_value, int pdefault_value) :
    name(pname), min_value(pmin_value), max_value(pmax_value), default_value(pdefault_value)
  {
  }
  std::string	name;
  int		min_value;
  int		max_value;
  int		default_value;
}		t_cvar;

class	Settings
=======
    MAP_DENSITY,
    MAP_LINEAR,
  };

class Settings
>>>>>>> 35c0cf39dea90a7423e4e792261ed64446d55473
{
public:
  Settings();
  ~Settings();

<<<<<<< HEAD
  bool	loadFile(const std::string &);
=======
  void	loadFile(const std::string &);
>>>>>>> 35c0cf39dea90a7423e4e792261ed64446d55473

  bool	cvarExist(cvar var) const;
  int	getVar(cvar var) const;
  void	setVar(cvar var, int value);
<<<<<<< HEAD
  eAction	getActionFromKey(Keycode key) const;
  int	getKeyFromAct(eAction act, std::vector<Keycode> &) const;
  void	setKey(Keycode key, eAction act);
  const std::string &getCodeFromKey(SDL_Keycode key) const;

  int	toNumber(const std::string &) const;
  bool	isAscii(const std::string &) const;

  bool	addKey(const std::string tab[3]);
  bool	addCvar(const std::string tab[3]);
=======
  eAction	getActionFromKey(keyCode key) const;
  int	getKeyFromAct(eAction act, std::vector<keyCode> &) const;
  void	setKey(keyCode key, eAction act);

  int	toNumber(const std::string &) const;
>>>>>>> 35c0cf39dea90a7423e4e792261ed64446d55473

private:
  bool	readFile(std::vector<std::string> &inst, const std::string &);
  void	parsInst(const std::vector<std::string> &inst);
<<<<<<< HEAD
  void	initCvar();
  Keycode	getKeyFromCode(const std::string &) const;

  std::vector<std::string>	_actionList;
  std::map<Keycode, eAction>	_keyMap;

  std::vector<t_cvar *>     	_cvarList;
  std::map<cvar, int>		_cvarMap;

  std::map<std::string, Keycode>	_speKeys;
=======
  void	addKey(const std::string tab[3]);
  void	addCvar(const std::string tab[3]);

  std::vector<std::string>	_actionList;
  std::map<keyCode, eAction>	_keyMap;

  std::vector<std::string>     	_cvarList;
  std::map<cvar, int>		_cvarMap;
>>>>>>> 35c0cf39dea90a7423e4e792261ed64446d55473
};

#endif /* _SETTINGS_H_ */
