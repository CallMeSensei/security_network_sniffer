#ifndef DISPLAY_H
# define DISPLAY_H

# include <sstream>

# include "my_lcurses.h"

class		Display
{
 private:
  int		nbPacket = 0;
  my_lcurses*	lcurses;
  ScrollTab*	tab;
  
 public:
  
  Display();
  ~Display();

  bool		init_Display();
  void		floop();
  bool		loop();
  void		end_Display();

  void		writePacket(std::string str);
};

#endif /* !DISPLAY_H */
