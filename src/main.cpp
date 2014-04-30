#include <Clock.hh>
#include <unistd.h>
#include <iostream>
#include "SdlContext.hh"
#include "Input.hh"

# define FPS 60

int main(int ac, char **av)
{
  gdl::SdlContext win;
  gdl::Clock	  clock;
  gdl::Input	  input;

  win.start(800, 600, "Bomberman");
  for(;;)
    {
      int time;

      if (input.getInput(SDL_QUIT))
	break;
      if ((time = clock.getElapsed()) < (FPS / 1000))
  	usleep(((FPS / 1000) - time) * 1000);
      win.updateClock(clock);
      win.updateInputs(input);
    }
  win.stop();
  return 0;
}
