// Catherine Markley && Chris Foley
// cse 20311- final project
// board.cpp
// implentation of board class

#include "board.h"

Board::Board()
{
  // creates board as initially empty
  // 0 = empty
  // 1 = taken
    for(int row = 0; row < numRows; row++)
    {
      for(int col = 0; col < numCols; col++)
      {
        array[row][col] = 0;
      }
    }
}

bool Board::isTaken(int row, int col)
{
  if(row < 0 ||
     row > numRows ||
     col < 0 ||
     col > numCols)
 {
   return true;
 } else {
   return array[row][col];
 }
}

void Board::Take(int row, int col)
{
  array[row][col] = 1;
}

void Board::clear()
{
  // makes an empty board
  // 0 = empty
  // 1 = taken
    for(int row = 0; row < numRows; row++)
    {
      for(int col = 0; col < numCols; col++)
      {
        array[row][col] = 0;
      }
    }
}

