#include <SdlContext.hh>
#include <unistd.h>
#include <Clock.hh>
#include <iostream>

# define FPS 60

int main(int ac, char **av)
{
  gdl::SdlContext win;
  gdl::Clock	  clock;

  win.start(800, 600, "Bomberman");

  for(int i = 0;i < 1000;i++)
    {
      int time;

      if ((time = clock.getElapsed()) < (FPS / 1000))
	usleep(((FPS / 1000) - time) * 1000);
      clock.update(0);
    }
  win.stop();
  return 0;
}
