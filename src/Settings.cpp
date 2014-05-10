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
}

Settings::~Settings()
{
  _keyMap.clear();
}

int	Settings::toNumber(const std::string &str)
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
