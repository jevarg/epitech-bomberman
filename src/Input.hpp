#ifndef INPUT_HPP_
# define INPUT_HPP_

# include <vector>
# include <Input.hh>

class	Input
{
public:
  Input();
  ~Input();

private:
  vector<bool>	_action;
  map<keycode, action>; //existe déjà, à récup dans string
  vector[action] = true/false;
};

#endif /* !INPUT_HPP_ */
