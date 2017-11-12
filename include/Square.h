#ifndef			SQUARE_H
# define		SQUARE_H

#include <iostream>
#include <cstring>
#include <ncurses.h>

class			Square
{
 private:
  std::string		name;
  WINDOW*		win;
  int			posx;
  int			posy;
  int			sizex;
  int			sizey;

  char			topLeft = '+';
  char			topRight = '+';
  char			bottomLeft = '+';
  char			bottomRight = '+';
  char			top = '-';
  char			bottom = '-';
  char			left = '|';
  char			right = '|';
  
 public:
  Square();
  ~Square();

  bool			init_Square(WINDOW* win, int px, int py, int sx, int sy, std::string name = "");
  
  void			setBorder(char topleft, char topright, char bottomleft, char bottomright, char top, char bottom, char left, char right);
  void			setPos(int px, int py);
  void			setSize(int px, int py);
  void			setName(std::string name);
  
  void			display();
  void			eraseDisplay();
};

#endif			/* !SQUARE_H */
