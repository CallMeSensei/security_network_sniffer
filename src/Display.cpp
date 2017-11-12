#include "Display.h"

Display::Display()
{

}

Display::~Display()
{

}

bool          Display::init_Display()
{
  int		sx;
  int		sy;
  
  lcurses = new my_lcurses();
  if (!lcurses->init_window())
    return false;
  lcurses->getSize(sx, sy);
  tab = lcurses->createScrollTab(0, 3, sx, 10);
  return true;
}

void          Display::floop()
{
  lcurses->setInputBlocking(true);
  while(loop());
}

bool          Display::loop()
{
  int ch = 0;
  
  lcurses->refresh();
  ch = lcurses->getInput();

  
  std::stringstream ss;
  
  ss << "-" << ch << "-";
  writePacket(ss.str());
  switch (ch)
    {
    case 265:
      return false;
    case 259:
      tab->moveUpScrollTab(1);
      break;
    case 258:
      tab->moveDownScrollTab(1);
      break;
    case 266:
      tab->moveDownScrollTab(1);
      break;
    case :
      tab->moveDownScrollTab(1);
      break;
    }
  return true;
}

void          Display::end_Display()
{
  lcurses->end_window();
}

void          Display::writePacket(std::string str)
{
  std::stringstream ss;
  
  ss << nbPacket << ")\t" << str;
  tab->writeScrollTab(ss.str());
  nbPacket++;
}
