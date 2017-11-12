#ifndef MY_LCURSES_H
# define MY_LCURSES_H

# include <iostream>
# include <cstring>
# include <ncurses.h>

# include "ScrollTab.h"
# include "Square.h"
# include "ntext.h"

class			my_lcurses
{
 private:
  WINDOW*		win;
  int			sizex;
  int			sizey;
  int			posx;
  int			posy;
  
 public:
  my_lcurses();
  ~my_lcurses();
  
  bool			init_window();
  void			end_window();
  void			setInputBlocking(bool block);

  
  bool			refresh();
  
  int			getInput();
  bool			getString(std::string &str);
  void			getSize(int &sx, int &sy);
  void			getCursorPos(int px, int py);
  void			setCursorPos(int px, int py);
  
  void			printAt(int px, int py, std::string str);
  void			printKey();
  
  ScrollTab*		createScrollTab(int px, int py, int sx, int sy);
  Square*		createSquare(int px, int py, int sx, int sy);
  ntext*		createNtext(int px, int py, std::string str = "");
};

#endif /* !MY_LCURSES_H */
