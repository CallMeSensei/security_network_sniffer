#include "ntext.h"

ntext::ntext()
{

}

ntext::~ntext()
{

}

bool			ntext::init_ntext(WINDOW* w, int px, int py, std::string str)
{
  win = w;
  posx = px;
  posy = py;
  setText(str);
  return true;
}

void			ntext::setPos(int px, int py)
{
  eraseDisplay();
  posx = px;
  posy = py;
  display();
}

void			ntext::setText(std::string str)
{
  eraseDisplay();
  text = str;
  display();
}

void			ntext::display()
{
  wmove(win, posy, posx);
  wprintw(win, "%s", text);
}

void			ntext::eraseDisplay()
{
  int			i = 0;
  
  wmove(win, posy, posx);
  while (i++ < (int)text.size())
    wprintw(win, " ");
}
