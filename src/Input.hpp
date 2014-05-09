#ifndef _INPUT_H_
# define _INPUT_H_

# include <map>

enum	eAction
  {
    A_UNKNOWN
  };

typedef unsigned char	keycode;

class Input
{
public:
  Input();
  ~Input();

  void	fillInput();

  std::vector<bool>	&getActions() const;
private:
  std::map<keycode, eAction>	_keyMap;
  std::vector<bool>		_actionState;
};

#endif /* _INPUT_H_ */
