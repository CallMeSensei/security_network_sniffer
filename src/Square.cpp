#include "Square.h"

Square::Square()
{

}

Square::~Square()
{

}

bool			Square::init_Square(WINDOW* w, int px, int py, int sx, int sy, std::string n)
{
  win = w;
  posx = px;
  posy = py;
  sizex = sx;
  sizey = sy;
  name = n;
  display();
  return true;
}

void			Square::setBorder(char topleft, char topright, char bottomleft, char bottomright, char t, char b, char l, char r)
{
  topLeft = topleft;
  topRight = topright;
  bottomLeft = bottomleft;
  bottomRight = bottomright;
  top = t;
  bottom = b;
  left = l;
  right = r;
}

void			Square::setPos(int px, int py)
{
  eraseDisplay();
  posx = px;
  posy = py;
  display();
}

void			Square::setSize(int sx, int sy)
{
  eraseDisplay();
  sizex = sx;
  sizey = sy;
  display();
}

void			Square::setName(std::string n)
{
  eraseDisplay();
  name = n;
  display();
}

void			Square::display()
{
  std::string		tmp;
  int			i = 0;

  wmove(win, posy, posx);
  wprintw(win, "%c", topLeft);
  wmove(win, posy, posx + sizex);
  wprintw(win, "%c", topRight);
  wmove(win, posy + sizey, posx);
  wprintw(win, "%c", bottomLeft);
  wmove(win, posy + sizey, posx + sizex);
  wprintw(win, "%c", bottomRight);
  
  while (i < sizex - 1)
    {
      mvwprintw(win, posy, posx + 1 + i, "%c", top);
      mvwprintw(win, posy + sizey, posx + 1 + i, "%c", bottom);
      i += 1;
    }
  i = 0;
  while (i < sizey - 1)
    {
      wmove(win, posy + 1 + i, posx);
      wprintw(win, "%c", left);
      wmove(win, posy + 1 + i, posx + sizex);
      wprintw(win, "%c", right);
      i++;
    }
  if (sizex - 2 <= 0)
    return;
  tmp = name.substr(0, sizex - 2);
  wmove(win, posy, posx + 1);
  //wprintw(win, "%s", tmp);
}

void			Square::eraseDisplay()
{

  int			i = 0;

  wmove(win, posy, posx);
  wprintw(win, " ");
  wmove(win, posy, posx + sizex);
  wprintw(win, " ");
  wmove(win, posy + sizey, posx);
  wprintw(win, " ");
  wmove(win, posy + sizey, posx + sizex);
  wprintw(win, " ");
  while (i < sizex - 2)
    {
      wmove(win, posy, posx + 1 + i);
      wprintw(win, " ");
      wmove(win, posy + sizey, posx + 1 + i);
      wprintw(win, " ");
      i++;
    }
  while (i < sizey - 2)
    {
      wmove(win, posy + 1 + i, posx);
      wprintw(win, " ");
      wmove(win, posy + 1 + i, posx + sizex);
      wprintw(win, " ");
      i++;
    }
}
