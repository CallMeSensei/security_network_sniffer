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
  lcurses->getInput(ch);
  
  switch (ch)
    {
    case 1:
      break;
    case 2:
      break;
    case 3:
      break;
    case 4:
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
