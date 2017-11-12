#include "my_lcurses.h"


my_lcurses::my_lcurses()
{
  
}

my_lcurses::~my_lcurses()
{
  
}

bool		my_lcurses::init_window()
{
  initscr();			/* Start curses mode */
  cbreak();
  keypad(stdscr, true);
  nodelay(stdscr, true);
  win = subwin(stdscr,0, 0, 0, 0);
  wrefresh(win);
  return true;
}

void		my_lcurses::end_window()
{
  nodelay(win, false);
  nocbreak();
  delwin(win);
  endwin();			/* End curses mode		  */
}

void		my_lcurses::setInputBlocking(bool block)
{
  nodelay(stdscr, !block);
}

bool		my_lcurses::refresh()
{
  getmaxyx(win, sizey, sizex);
  getyx(win, posy, posx);
  wrefresh(win);
  return (true);
}

int		my_lcurses::getInput()
{
  return (getch());
}

bool		my_lcurses::getString(std::string &str)
{
  char tmp[512];
  getstr(tmp);/* Wait for user input */
  str = tmp;
  return (false);
}

void		my_lcurses::getSize(int &sx, int &sy)
{
  getmaxyx(win, sizey, sizex);
  sx = sizex - 1;
  sy = sizey - 1;
}

void		my_lcurses::getCursorPos(int px, int py)
{
  px = px;
  py = py;
  px = posx;
  py = posy;
}

void		my_lcurses::setCursorPos(int px, int py)
{
  px = px;
  py = py;
  wmove(win, py, px);
  posx = px;
  posy = py;
}

void		my_lcurses::printAt(int px, int py, std::string str)
{
  setCursorPos(px, py);
  wprintw(win, "%s", str);
}

void		my_lcurses::printKey()
{
  int		ch;
  
  ch = getch();			/* Wait for user input */
  if (ch != ERR)
    {
      wprintw(win, "ascii =\"%c\" hexa=\"%x\"\n", ch, ch);	/* Print Hello World		  */
      wrefresh(win);			/* Print it on to the real screen */
    }
}

ScrollTab*	my_lcurses::createScrollTab(int px, int py, int sx, int sy)
{
  ScrollTab* stab = new ScrollTab();

  stab->init_ScrollTab(win, px, py, sx,sy);
  wrefresh(win);
  refresh();
  return (stab);
}

Square*		my_lcurses::createSquare(int px, int py, int sx, int sy)
{
  Square* square = new Square();
  
  square->init_Square(win, px, py, sx, sy);
  wrefresh(win);
  return (square);
}

ntext*		my_lcurses::createNtext(int px, int py, std::string str)
{
  ntext*	text = new ntext();
  
  text->init_ntext(win, px, py, str);
  wrefresh(win);
  return (text);
}
