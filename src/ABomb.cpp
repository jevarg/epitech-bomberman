#include "ABomb.hpp"
#include "Exception.hpp"
#include "GameEngine.hpp"
#include "Map.hpp"
#include "Flame.hpp"

ABomb::ABomb(int x, int y, IObject *bombModel)
  : AEntity(x, y, BOMB, bombModel), _mutex(), _condvar()
{
  pthread_t         thread;

  if (pthread_create(&thread, NULL, &handle_bomb_thread, this) != 0)
    throw (Exception("Can't create ABomb's thread"));
  _thread = thread;
}

ABomb::~ABomb()
{
}

void	ABomb::explode(Map &map)
{
  setFire(_x, _y, UNKNOWN, _range, map);
}

/* TODO: check for walls, handle bomb power */
void	ABomb::setFire(int x, int y, eAction direction, int range, Map &map)
{
  while (map.getEntity(x, y))
    map.setEntity(x, y, FREE);
  map.addEntity(new Flame(x, y, NULL)); // add model via singleton here
  switch (direction)
    {
    case UNKNOWN:
      setFire(x, y - 1, FORWARD, range - 1, map);
      setFire(x, y + 1, BACK, range - 1, map);
      setFire(x - 1, y, LEFT, range - 1, map);
      setFire(x + 1, y, RIGHT, range - 1, map);
      break;
    case FORWARD:
      setFire(x, y - 1, FORWARD, range - 1, map);
      break;
    case BACK:
      setFire(x, y + 1, BACK, range - 1, map);
      break;
    case LEFT:
      setFire(x - 1, y, LEFT, range - 1, map);
      break;
    case RIGHT:
      setFire(x + 1, y, RIGHT, range - 1, map);
      break;
    default:
      break;
    }
}

void	*handle_bomb_thread(void *arg)
{
  (void) arg;
  return (NULL);
}
