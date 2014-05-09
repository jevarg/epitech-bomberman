#include "Settings.hpp"

Settings::Settings()
{
}

Settings::~Settings()
{
  _keyMap.clear();
}

void	Settings::parsInst(const std::vector<std::string> &inst)
{
  v_instCit it = inst.begin();
  v_instCit end = inst.end();
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
}
