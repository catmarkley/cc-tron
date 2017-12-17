// Catherine Markley Chris Foley
// cse 20311 - final project
// board.h
// interface for board class

const int numRows = 50;
const int numCols = 80;

class Board {

  public:
    Board();
    bool isTaken(int, int);
    void Take(int, int);
    void clear();
  public:
    bool array[numRows][numCols];
};

