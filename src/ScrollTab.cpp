#include "ScrollTab.h"

ScrollTab::ScrollTab()
{
  
}

ScrollTab::~ScrollTab()
{

}

bool                  ScrollTab::init_ScrollTab(WINDOW* w, int px, int py, int sx, int sy, std::string n)
{
  win = subwin(w, sy - 1, sx - 1, py + 1, px + 1);
  sizex = sx - 1;
  sizey = sy - 1;
  posx = 0;
  posy = 0;
  name = n;
  square = new Square();
  square->init_Square(w, px, py, sx, sy, n);
  display();
  return (true);
}

void                  ScrollTab::setPos(int px, int py)
{
  eraseDisplay();
  posx = px;
  posy = py;
  square->setPos(px ,py);
  display();
}

void                  ScrollTab::setSize(int sx, int sy)
{
  eraseDisplay();
  sizex = sx;
  sizey = sy;
  square->setSize(sx ,sy);
  display();
}

void			ScrollTab::setName(std::string n)
{
  name = n;
  square->setName(n);
}

void			ScrollTab::writeScrollTab(std::string str)
{ 
  histo.push_back(str);
  if (sizex <= 0)
    return;
  if (sizey <= 0)
    return;
  if (idx + 1 == (int)histo.size())
    {
      for (auto line: formatElem(str))
	{
	  if ((int)content.size() >= sizey)
	    content.erase(content.begin());
	  content.push_back(line);
	}
      idx++;
    }
  else
    {
      moveAtScrollTab(idx);
    }
  eraseDisplay();
  display();
}

void		      ScrollTab::eraseDisplay()
{
  int			y = 0;
  int			x;

  if (sizey <= 0 )
    return;
  if (sizex <= 0 )
    return;
  while (y < sizey)
    {
      wmove(win, posy + y, posx);
      x = 0;
      while (x < sizex)
	{
	  wprintw(win, " ");
	  x++;
	}
      y++;
    }
  wrefresh(win);
}

std::vector<std::string>	ScrollTab::formatElem(std::string str)
{
  int				pos = 0;
  std::vector<std::string>	tmp;
  
  while ((int)str.size() > pos)
    {
      tmp.push_back(str.substr(pos, sizex));
      pos += sizex;
    }
  return tmp;
}

void                  ScrollTab::display()
{
  int			y = 0;

  for (auto elem: content)
    {
      wmove(win, posy + y, posx);
      wprintw(win, "%s", elem.c_str());
      y++;
    }
  wrefresh(win);
}

void                  ScrollTab::clearContent()
{
  eraseDisplay();
  content.clear();
  histo.clear();
}

void			ScrollTab::moveAtScrollTab(int i)
{
  int				p;
  std::vector<std::string>	tmp;
  std::vector<std::string>::reverse_iterator	it;
  
  if (i < 0)
    i = 0;
  if (i >= (int)histo.size())
    i = histo.size() - 1;
  content.clear();
  idx = i;
  while ((int)content.size() <= sizey - 1 && (int)histo.size() > i && i >= 0)
    {
      tmp = formatElem(histo[i--]);
      p = tmp.size() - 1;
      while(p >= 0)
	{
	  if ((int)content.size() <= sizey)
	    {
	      content.insert(content.begin(), tmp[p]);
	    }
	  p--;
	}
    }
  eraseDisplay();
  display();
}

void                  ScrollTab::moveUpScrollTab(int i)
{
  moveAtScrollTab(idx - i);
}

void                  ScrollTab::moveDownScrollTab(int i)
{
  moveAtScrollTab(idx + i);
}

void                  ScrollTab::moveAtEndScrollTab()
{
  moveAtScrollTab(histo.size());
}

std::string		ScrollTab::getContent()
{
  std::string		tmp;

  for (auto elem: histo)
      tmp += elem + "\n";
  return tmp;
}
