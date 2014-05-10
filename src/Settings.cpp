#include "Settings.hpp"
#include <iterator>

Settings::Settings()
{
  _actionList.push_back("forward");
  _actionList.push_back("back");
  _actionList.push_back("left");
  _actionList.push_back("right");
  _actionList.push_back("activate");
}

Settings::~Settings()
{
  _keyMap.clear();
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
      std::cout << tab[0] << " " << tab[1] << " " << tab[2] << std::endl;
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
  std::map<keyCode, eAction>::iterator it;

  for (it = _keyMap.begin(); it != _keyMap.end(); ++it)
    {
      std::cout << it->first << " => " << _actionList[(int)it->second] << std::endl;
    }
}
