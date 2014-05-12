#ifndef _INPUT_H_
# define _INPUT_H_

# include "Settings.hpp"

class Input
{
public:
  Input();
  ~Input();

  void	getInput(const Settings &set);
  bool	operator[](eAction act);
  bool	operator[](keyCode key);

private:
  std::vector<bool>		_actionState;
  std::map<keyCode, bool>	_boundKey;
};

#endif /* _INPUT_H_ */
