#ifndef	NTEXT_H
# define NTEXT_H

# include <ncurses.h>
# include <string>

class			 ntext
{
  std::string		text;
  WINDOW*		win;
  int			posx;
  int			posy;
  
 public:
  ntext();
  ~ntext();

  bool			init_ntext(WINDOW* w, int px, int py, std::string str);

  void			setPos(int px, int py);
  void			setText(std::string str);
  
  void			display();
  void			eraseDisplay();
};

#endif /* !NTEXT_H*/
