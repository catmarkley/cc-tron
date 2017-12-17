// Catherine Markley && Chris Foley
// cse 20311 - final project
// snake.cpp
// implentation for snake class

#include "snake.h"

// Constructors
  Snake::Snake()
  {
    setDirec('u');
    setRow(0);
    setCol(0);
    setRed(255);
    setGreen(255);
    setBlue(255);
    setFirstmove(0);
    setWins(0);
    setAlive(1);
    setPlaying(1);
  }

  Snake::Snake(char c, int row, int col, int r, int g, int b, bool x, int w, bool a, bool p)
  {
    setDirec(c);
    setRow(row);
    setCol(col);
    setRed(r);
    setGreen(g);
    setBlue(b);
    setFirstmove(x);
    setWins(w);
    setAlive(a);
    setPlaying(p);
  }

// get functions
  char Snake::getDirec()      { return Direc;     }
  int  Snake::getRow()        { return Row;       }
  int  Snake::getCol()        { return Col;       }
  int  Snake::getRed()        { return Red;       }
  int  Snake::getGreen()      { return Green;     }
  int  Snake::getBlue()       { return Blue;      }
  bool Snake::getFirstmove()  { return Firstmove; }
  int  Snake::getWins()       { return Wins;      }
  bool Snake::getAlive()      { return Alive;     }
  bool Snake::getPlaying()    { return Playing;   }

// set functions
  void Snake::setDirec(char x)      { Direc     = x; }
  void Snake::setRow(int x)         { Row       = x; }
  void Snake::setCol(int x)         { Col       = x; }
  void Snake::setRed(int x)         { Red       = x; }
  void Snake::setGreen(int x)       { Green     = x; }
  void Snake::setBlue(int x)        { Blue      = x; }
  void Snake::setFirstmove(bool x)  { Firstmove = x; }
  void Snake::setWins(int x)        { Wins      = x; }
  void Snake::setAlive(bool x)      { Alive     = x; }
  void Snake::setPlaying(bool x)    { Playing   = x; }

