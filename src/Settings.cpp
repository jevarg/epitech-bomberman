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
  (void)inst;
}

void	Settings::readFile(std::vector<std::string> &inst,
			   const std::string &filename)
{
  std::ifstream file(filename.c_str());
  std::string	line;

  if (file.is_open())
    {
      while (std::getline(file, line))
	{
	  std::cout << line << std::endl;
	  inst.push_back(line);
	}
      file.close();
    }
}

void	Settings::loadFile(const std::string &filename)
{
  std::vector<std::string>	inst;

  readFile(inst, filename);
  parsInst(inst);
}
