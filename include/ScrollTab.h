#ifndef				SCROLLTAB_H
# define			SCROLLTAB_H

# include			<ncurses.h>
# include			<string>
# include			<vector>
# include			<cstring>
# include			<iostream>

# include			"Square.h"

class				ScrollTab
{
 private:
  std::string			name;
  WINDOW*			win;
  Square*			square;
  int				sizex;
  int				sizey;
  int				posx;
  int				posy;
  int				idx;
  std::vector<std::string>	histo;
  std::vector<std::string>	content;

 public:
  ScrollTab();
  ~ScrollTab();

  bool				init_ScrollTab(WINDOW* w, int px, int py, int sx, int sy, std::string name = "");
  
  void				setPos(int px, int py);
  void				setSize(int sx, int sy);
  void				setName(std::string n);
  
  void				writeScrollTab(std::string str);
  std::vector<std::string>	formatElem(std::string str);
  void				eraseDisplay();
  void				display();
  void				clearContent();
  
  void				moveAtScrollTab(int i);
  void				moveUpScrollTab(int i);
  void				moveDownScrollTab(int i);
  void				moveAtEndScrollTab();

  std::string			getContent();
};

#endif		/* !SCROLLTAB_H */
