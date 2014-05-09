#include "Input.hpp"

Input::Input()
{
}

Input::~Input()
{
  _keyMap.clear();
  _actionState.clear();
}

void	Input::fillInput()
{

}

std::vector<bool>	&Map::getActions() const
{
  return (_actionState.begin());
}
