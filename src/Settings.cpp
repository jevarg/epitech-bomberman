#include "Settings.hpp"
#include <iterator>

Settings::Settings()
{
  _actionList.push_back("forward");
  _actionList.push_back("back");
  _actionList.push_back("left");
  _actionList.push_back("right");
  _actionList.push_back("activate");

  _cvarList.push_back("com_maxFps");
  _cvarList.push_back("cg_fov");
  _cvarList.push_back("r_windowHeight");
  _cvarList.push_back("r_windowWidth");
  _cvarList.push_back("m_mapHeight");
  _cvarList.push_back("m_mapWidth");
  _cvarList.push_back("s_mapDensity");
  _cvarList.push_back("s_mapLinear");
}

Settings::~Settings()
{
  _keyMap.clear();
}

int	Settings::toNumber(const std::string &str) const
{
  int	num;
  std::istringstream(str) >> num;

  return (num);
}

void	Settings::addCvar(const std::string tab[3])
{
  v_instit	listit;
  v_instit	listend = _cvarList.end();
  int		cvarValue = toNumber(tab[2]);

  for (listit = _cvarList.begin(); listit != listend; ++listit)
    {
      if (*listit == tab[1])
	{
	  _cvarMap.insert(std::pair<cvar, int>
			  (static_cast<cvar>(std::distance(_cvarList.begin(), listit)),
			   cvarValue));
	  break ;
	}
    }

}

void	Settings::addKey(const std::string tab[3])
{
  v_instit	listit;
  v_instit	listend = _actionList.end();

  for (listit = _actionList.begin(); listit != listend; ++listit)
    {
      if (*listit == tab[2])
	{
	  _keyMap.insert(std::pair<keyCode, eAction>
			 (tab[1].at(0), static_cast<eAction>
			  (std::distance(_actionList.begin(), listit))));
	  break ;
	}
    }
}

void	Settings::parsInst(const std::vector<std::string> &inst)
{
  v_instCit	it = inst.begin();
  v_instCit	end = inst.end();
  std::string	tab[3];

  while (it != end)
    {
      std::istringstream iss(*it);
      for (int i = 0; i < 3; ++i)
	if (!(iss >> tab[i]))
	  {
	    std::cerr << "Missing arguments for " << tab[0] << std::endl;
	    break ;
	  }
      if (tab[0] == "bind" && tab[1].size() == 1)
	addKey(tab);
      else if (tab[0] == "set")
	addCvar(tab);
      ++it;
    }
}

bool	Settings::readFile(std::vector<std::string> &inst,
			   const std::string &filename)
{
  std::ifstream file(filename.c_str());
  std::string	line;

  std::cout << "dfrth" << std::endl;
  if (file.is_open())
    {
      while (std::getline(file, line))
	{
	  if (line.find_first_not_of(" \t\n\v\f\r") != std::string::npos)
	    inst.push_back(line);
	}
      file.close();
      return (true);
    }
  else
    std::cerr << "Can't open file " << filename << std::endl;
  return (false);
}

void	Settings::loadFile(const std::string &filename)
{
  std::vector<std::string>	inst;

  if (readFile(inst, filename))
    parsInst(inst);

  std::map<keyCode, eAction>::iterator kit;
  std::map<cvar, int>::iterator cit;

  for (kit = _keyMap.begin(); kit != _keyMap.end(); ++kit)
    {
      std::cout << kit->first << " => " << kit->second << " => "
		<<  _actionList[(int)kit->second] << std::endl;
    }

  for (cit = _cvarMap.begin(); cit != _cvarMap.end(); ++cit)
    {
      std::cout << _cvarList[(int)cit->first] << ": "<< cit->first <<
	" => " << cit->second << std::endl;
    }
}

bool	Settings::cvarExist(cvar var) const
{
  return (_cvarMap.find(var) != _cvarMap.end());
}

/*
** On the methode below, iterator 'it' would never be equal to map.end()
** if cvarExist is used.
*/

int	Settings::getVar(cvar var) const
{
  std::map<cvar, int>::const_iterator	it;

  if ((it = _cvarMap.find(var)) == _cvarMap.end())
    return (0);
  return (it->second);
}

void	Settings::setVar(cvar var, int value)
{
  _cvarMap[var] = value;
}

eAction	Settings::getActionFromKey(keyCode key) const
{
  std::map<keyCode, eAction>::const_iterator   it;

  if ((it = _keyMap.find(key)) == _keyMap.end())
    return (UNKNOWN);
  return (it->second);
}

/*
** getKeyFromAct Will fill a vector of key and return the number of key inserted
** A vector must be used considering we handle multibinding
*/

int	Settings::getKeyFromAct(eAction act, std::vector<keyCode> &keySet) const
{
  std::map<keyCode, eAction>::const_iterator   it;
  std::map<keyCode, eAction>::const_iterator   end;
  int	nbKey = 0;

  for (it = _keyMap.begin(), end = _keyMap.end(); it != end; ++it)
    {
      if (it->second == act)
	{
	  keySet.push_back(it->first);
	  ++nbKey;
	}
    }
  return (nbKey);
}

void	Settings::setKey(keyCode key, eAction act)
{
  _keyMap[key] = act;
}
