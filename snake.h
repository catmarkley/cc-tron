// Catherine Markley Chris Foley
// cse 20311 - final project
// snake.h
// interface for snake class

class Snake {

  public:
    Snake();
    Snake(char, int, int, int, int, int, bool, int, bool, bool);
    char getDirec();
    int getRow();
    int getCol();
    int getRed();
    int getGreen();
    int getBlue();
    int getWins();
    bool getAlive();
    bool getFirstmove();
    bool getPlaying();
    void setDirec(char);
    void setRow(int);
    void setCol(int);
    void setRed(int);
    void setGreen(int);
    void setBlue(int);
    void setFirstmove(bool);
    void setWins(int);
    void setAlive(bool);
    void setPlaying(bool);
  public:
   char Direc;
   int Row;
   int Col;
   int Red;
   int Green;
   int Blue;
   bool Firstmove;
   int Wins;
   bool Alive;
   bool Playing;

};

