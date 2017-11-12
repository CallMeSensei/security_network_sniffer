#ifndef DISPLAY_H
# define DISPLAY_H

# include <sstream>
# include <vector>

# include "my_lcurses.h"
# include "Packet.hh"

class		Display
{
 private:
  std::vector<Packet*> packetList;
  int		nbPacket = 0;
  my_lcurses*	lcurses;
  ScrollTab*	tab;
  ScrollTab*	lowtab;
  int		idx = 0;
  
 public:
  
  Display();
  ~Display();

  bool		init_Display();
  void		floop();
  bool		loop();
  void		end_Display();

  void		writePacket(Packet *p);
};

#endif /* !DISPLAY_H */
