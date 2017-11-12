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
  tab = lcurses->createScrollTab(0, 3, sx, 12);
  lowtab = lcurses->createScrollTab(0, 16, sx, sy - 16);
  return true;
}

void          Display::floop()
{
  lcurses->setInputBlocking(true);
  while(loop());
}

bool          Display::loop()
{
  int		ch = 0;
  int		i;
  
  lcurses->refresh();
  ch = lcurses->getInput();
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
      tab->moveAtEndScrollTab();
      break;
    }
  
  i = tab->getIdx();
  if (i != idx)
    {
      idx = i;
      if ((int)packetList.size() > idx && idx >= 0)
	{
	  lowtab->clearContent();
	  lowtab->writeScrollTab(packetList[idx]->to_string());
	}
    }
  return true;
}

void          Display::end_Display()
{
  lcurses->end_window();
}

void          Display::writePacket(Packet *p)
{
  std::stringstream ss;

  packetList.push_back(p);
  ss << nbPacket << ")\t" << p->to_string();
  tab->writeScrollTab(ss.str());
  nbPacket++;
}
