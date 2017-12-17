// Catherine Markley && Chris Foley
// cse 20311 - final project
// project.cpp
// main driver for bmtron game.
// bmtron is a multiplayer snake game in which the goal is to stay alive as long as
// possible by avoiding the tails of yourself and the other player

#include <iostream> // stream stuff
#include <unistd.h> // usleep
#include <vector>   // vector class
#include <math.h>   // ceil

using namespace std;

#include "gfx.h"    // drawing capabilities and funcitons
#include "board.h"  // board class
#include "snake.h"  // snake class

// prototype functions
  int menu(vector<Snake> &, double, double);
  void drawSolidSquare(double, double, double);
  bool endmenu(vector<Snake>, double, double, int);
  void drawtitle(int, int, int [][3]);

int main()
{
  // Open window
    int cell_size = 10;
    int xsize = numCols * cell_size;
    int ysize = numRows * cell_size;
    gfx_open(xsize, ysize, "CC-Tron");

  // Set all parameters to true
    bool round = true;
    bool game = true;
	bool running = true;
    bool tester;
  // create a vector of numbers
    const char *  numbers[] = {"0","1","2","3","4","5"};

  // create vector of blank snakes
    vector<Snake> players;
    for(int i = 0; i < 4; i++)
    {
      Snake player;
      players.push_back(player);
    }
    int n = 4;
    int cp;

  while(running)
  {
    // open and run menu
      cp = menu(players, xsize, ysize);
      gfx_clear();
      if(cp == 27)
        return 1;

    // Set up a game
      // Declare board and snakes
        Board myboard;

      // Declare input variable
	    char user_input;

	  // Get ready to play game
	    game = true;
	    // set snake wins to zero
  	      for(int i = 0; i < n; i++)
 	        players[i].setWins(0);

    // Play Game
      while(game)
      {
        // Set up Round
/*          // draw grid
            gfx_color(25, 25, 25);
            double dash = 2;
            for(int i = 0; i < xsize; i++)
            {
              for(int x3 = 0; x3 < ysize; x3 += 2*dash)
                gfx_line((i*cell_size), x3, (i*cell_size), x3 + dash);
            }
            for(int i = 0; i < ysize; i++)
            {
              for(int y3 = 0; y3 < xsize; y3 += 2*dash)
                gfx_line(y3, (i*cell_size), y3 + dash, (i*cell_size));
            }
*/
          // reset snakes
            int actual = 0;
            for(int i = 0; i < n; i++)
            {
              if(players[i].getPlaying())
              {
                players[i].setDirec('u');
                players[i].setRow(ceil(numRows/2));
                players[i].setCol(numCols - ceil(((actual++)+1)*numCols/(cp+1)));
                players[i].setFirstmove(false);
                players[i].setAlive(true);
              }
            }

      	  // Reset board
      	    // Clear board
              myboard.clear();

            // Mark starting locations as taken

              for(int i = 0; i < n; i++)
              {
                if(players[i].getPlaying())
                {
                  myboard.Take(players[i].getRow(), players[i].getCol());
                }
	          }

          // Get ready to play round
            round = true;

       	// Play Round
	      while(round)
    	  {
        	// Draw snake for each player
	          for(int i = 0; i <= n-1; i++)
    	      {
                if(players[i].getPlaying())
                {
          	      // get positions and RGB values
            	    int x = 10*players[i].getCol();
	                int y = 10*players[i].getRow();
    	            int R = players[i].getRed();
        	        int G = players[i].getGreen();
            	    int B = players[i].getBlue();
	                char direc = players[i].getDirec();

    	          // Draw snake
        	        if(direc == 'u' || direc == 'd') // This means the direction is up or down
            	    {
	                  // draw side  black border
	                    gfx_color(0,0,0);
    	                gfx_line(x + cell_size, y, x + cell_size, y + cell_size);
        	            gfx_line(x, y + cell_size, x, y);
            	      // draw 3rd border and shade
                	    if(direc == 'u')
	                    {
    	                  // draw 3rd border
        	                gfx_line(x, y, x + cell_size, y);
              	          // shade
                	        gfx_color(R, G, B);
                    	    for(int i = 1; i <= cell_size; i++)
                        	  gfx_line(x + 1 , y + i, x + cell_size - 1, y + i);
	                    } else {
    	                  // draw 3rd border
        	                gfx_line(x, y + cell_size, x + cell_size, y + cell_size);
            	          // shade
                	        gfx_color(R, G, B);
                    	    for(int i = 0; i < cell_size; i++)
                        	  gfx_line(x + 1 , y + i, x + cell_size - 1, y + i);
	                    }

    	            } else { // This means the direction is right or left
        	          // draw border
            	        gfx_color(0,0,0);
                	    gfx_line(x, y, x + cell_size, y);
	                    gfx_line(x + cell_size, y + cell_size, x, y + cell_size);
  		              // draw 3rd border and shade
        	            if(direc == 'r')
            	        {
			    	      // draw 3rd border
  		            	    gfx_line(x + cell_size, y, x + cell_size, y + cell_size);
	                      // shade
    	                    gfx_color(R, G, B);
        	                for(int i = 0; i < cell_size; i++)
            	              gfx_line(x + i, y + 1, x + i, y + cell_size - 1);
	            	    } else {
		    	    	  // draw 3rd border
	                        gfx_line(x, y, x, y + cell_size);
    	                  // shade
        	                gfx_color(R, G, B);
            	            for(int i = 1; i <= cell_size; i++)
                	          gfx_line(x + i, y + 1, x + i, y + cell_size - 1);
	                    }
    	            }
        	    }
        	  }

	        // respond to input (or wait for each player to make their first move)
    	      // see if players have made their first move
        	    bool allready = false;
            	int sum = 0;
	            for(int i = 0; i < n; i++)
    	        {
	              if(players[i].getPlaying())
          	        sum += players[i].getFirstmove();
            	}

	            if(sum >= cp)
    	          allready = true;

	        // while loop to loop until all players are ready to play
    	      while(gfx_event_waiting() || !(allready))
        	  {
            	user_input = gfx_wait();

	            switch (user_input)
    	        {
        	      // player 0 controls (ARROW KEYS)
            	    case 'Q':
	                  players[0].setDirec('l');
	                  players[0].setFirstmove(true);
	                break;
	                case 'R':
	                  players[0].setDirec('u');
	                  players[0].setFirstmove(true);
	                break;
	                case 'S':
	                  players[0].setDirec('r');
	                  players[0].setFirstmove(true);
	                break;
	                case 'T':
	                  players[0].setDirec('d');
	                  players[0].setFirstmove(true);
	                break;
	              // player 1 controls (WSAD)
	                case 'w':
	                  players[1].setDirec('u');
	                  players[1].setFirstmove(true);
	                break;
	                case 'a':
	                   players[1].setDirec('l');
	                   players[1].setFirstmove(true);
	                break;
	                case 's':
	                  players[1].setDirec('d');
	                  players[1].setFirstmove(true);
	                break;
	                case 'd':
	                  players[1].setDirec('r');
	                  players[1].setFirstmove(true);
	                break;
	              // player 2 controls (YGHJ)
	                case 'y':
	                  players[2].setDirec('u');
	                  players[2].setFirstmove(true);
	                break;
	                case 'g':
	                  players[2].setDirec('l');
	                  players[2].setFirstmove(true);
	                break;
	                case 'h':
	                  players[2].setDirec('d');
	                  players[2].setFirstmove(true);
	                break;
	                case 'j':
	                  players[2].setDirec('r');
	                  players[2].setFirstmove(true);
	                break;
	              // player 3 controls (PL;')
	                case 'p':
	                   players[3].setDirec('u');
	                   players[3].setFirstmove(true);
	                break;
	                case 'l':
	                  players[3].setDirec('l');
	                  players[3].setFirstmove(true);
	                break;
	                case ';':
	                  players[3].setDirec('d');
	                  players[3].setFirstmove(true);
	                break;
	                case '\'':
	                  players[3].setDirec('r');
	                  players[3].setFirstmove(true);
	                break;

	              // quit if esc
	                case 27:
	                  return 1;
	            }

	            // checks if each player has selected a starting move
	              sum = 0;
	              for(int i = 0; i < n; i++)
	              {
                    if(players[i].getPlaying())
	                  sum += players[i].getFirstmove();
	              }

    	          if(sum >= cp)
	                allready = true;
	          }

	        // update location
	          for(int i = 0; i < n; i++)
	          {
	            if(players[i].getAlive() && players[i].getPlaying())
	            {
	              switch(players[i].getDirec())
	              {
	                case 'l':
	                  players[i].setCol(players[i].getCol() - 1);
	                break;
	                case 'u':
	                  players[i].setRow(players[i].getRow() - 1);
	                break;
	                case 'r':
	                  players[i].setCol(players[i].getCol() + 1);
	                break;
	                case 'd':
	                  players[i].setRow(players[i].getRow() + 1);
	                break;
	              }
	            }
	          }

	        // flush and sleep
	          gfx_flush();
	          usleep(60000);

	        // check for death
	          // check if hit wall
	            for(int i = 0; i < n; i++)
	            {
	              if(players[i].getPlaying())
	              {
  	                if(
	                   // Snake hit wall
	                     players[i].getCol() == numCols   ||
  	                     players[i].getCol() == -1        ||
	                     players[i].getRow() == numRows   ||
	                     players[i].getRow() == -1        ||
	                   // Snake hit tail
	                     myboard.isTaken(players[i].getRow(), players[i].getCol())
	                  )
	                {
	                  // this kills the snake
	                    players[i].setAlive(false);
	                }

				    if(players[i].getAlive()){
  	                // Update board to include new spots
    	              myboard.Take(players[i].getRow(), players[i].getCol());
	                }
	              }
			    }

	        // Checking if last alive
 	          // count how many others are alive
	            int count = 0;
	            for(int i = 0; i < n; i++)
	            {
			      if(players[i].getAlive() && players[i].getPlaying())
			        count++;
			    }
			  // if there is only one alive, end round. find winner, add a win
  			    // (this includes if the count is zero, which occurs when two
			    // players die at the same time. since both players die, neither
			    // receive points)
                if(count <= 1)
                {
	              round = false;
	              for(int i = 0; i < n; i++)
	              {
	                if(players[i].getAlive() && players[i].getPlaying())
	                  players[i].setWins(players[i].getWins() + 1);
	              }
	            }

    	  }  // End of Round ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	    // Check scores
	      // clear screen
	        gfx_clear();

          // Display score
            // Display numbers
              for(int i = 0; i < n; i++)
              {
	            if(players[i].getPlaying())
	            {
	              gfx_color(players[i].getRed(), players[i].getGreen(), players[i].getBlue());
	              gfx_text((i+1)*10 + 2, 10, numbers[players[i].getWins()]);
	            }
	          }

          // Check for winner
	        for(int i = 0; i < n; i++)
	        {
	          if(players[i].getWins() == 5 && players[i].getPlaying())
	          {
	            game = false;
	            gfx_clear();
  	            tester = endmenu(players, xsize, ysize, i);
  	            gfx_clear();

  	          }
	        }
	} // End of Game ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

      if(tester)
        running = true;
      else
        running = false;

  } // End of running~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

  return 0;

} // ends int main()

int menu(vector<Snake> &players, double xsize, double ysize)
{
  // make all players playing
    for(int p = 0; p <= 3; p++)
      players[p].setPlaying(true);

  // Declare color array
    int colors[][3] = {  {181, 43, 43},  // color 1: RED
                         {224, 168, 38}, // color 2: ORANGE
                         { 42, 54, 183}, // color 3: BLUE
                         {226, 223, 34}, // color 4: YELLOW
                         {153, 27, 142}, // color 5: PURPLE
                         { 27, 135, 20}, // color 6: GREEN
                       };

  // Declare array of char of number array
    const char * playernames[] = {"Player 0:", "Player 1:", "Player 2:", "Player 3:"};

  // display title
    drawtitle(xsize, ysize, colors);

  // display "pick color!"
    gfx_color(255,255,255);
    gfx_text(6*xsize/20, 8*ysize/20 - 12, "Pick your color!");

  // display must have at least two players
    gfx_text(5*xsize/20, 18.5*ysize/20, "*At least two players must play");

  // Display each player and options
    for(int p = 0; p <= 3; p++)
    {
      // Title each player
        gfx_color(255, 255, 255);
        gfx_text(3*xsize/20, (8 + 2.6*p)*ysize/20, playernames[p]);

      // Draw colored squares
        for (int i = 0; i < 6; i++)
        {
          // Pick color from array
            gfx_color(colors[i][0], colors[i][1], colors[i][2]);
          // Draw square
            drawSolidSquare((4+i)*xsize/20, (8.5 + 2.6*p)*ysize/20, xsize/20);
        }

      // Draw white box with x
        gfx_color(255,255,255);
        drawSolidSquare((10)*xsize/20, (8.5 + 2.6*p)*ysize/20, xsize/20);
        gfx_color(255,0,0);
        gfx_line(10*xsize/20, (8.5 + 2.6*p)*ysize/20, 10*xsize/20 + xsize/20, (8.5 + 2.6*p)*ysize/20 + xsize/20);
        gfx_line(10*xsize/20, (8.5 + 2.6*p)*ysize/20 + xsize/20, 10*xsize/20 + xsize/20, (8.5 + 2.6*p)*ysize/20);
    }

  // place controls
    gfx_color(255,255,255);
    // Player 0 : arrows
      gfx_text(11.5*xsize/20 - 12, 9.4*ysize/20, "Arrows");
    // Player 1 : WASD
      gfx_text(11.5*xsize/20, 12*ysize/20,"W");
      gfx_text(11.5*xsize/20 - 12, 12*ysize/20 + 12, "A S D");
    // Player 2 : YGHJ
      gfx_text(11.5*xsize/20, 14.5*ysize/20, "Y");
      gfx_text(11.5*xsize/20 - 12, 14.5*ysize/20 + 12,"G H J");
    // Player 3 : PL;'
      gfx_text(11.5*xsize/20, 17*ysize/20, "P");
      gfx_text(11.5*xsize/20 - 12, 17*ysize/20 + 12, "L ; '");

  // Draw play button
    gfx_color(115, 115, 115);
    drawSolidSquare(13*xsize/20,  12*ysize/20, xsize/20);
    drawSolidSquare(14*xsize/20,  12*ysize/20, xsize/20);
    gfx_color(0, 100, 255);
    gfx_text(14*xsize/20 - 15, 12.5*ysize/20 + 12, "PLAY!");

  // set up boolean
    bool setup = true;
    // this boolean runs through the menu, manually clicking the first four options

  // loop to continue to check for input
    while(true)
    {
      // run 4 times for the setup
      for(int setuprun = 0; setuprun <= 3; setuprun++)
      {
        //  If the there is an event or if its setting up
   	      if(gfx_event_waiting() || setup)
  	      {
            char c;
            if(!setup)
            {
              c = gfx_wait();
            } else {
              // force click if setting up
                c = 1;
            }

            // check if its an ESC press
              if(c == 27)
                return 27;

            // check if its a click
              if(c == 1)
              {

                int x, y;
                if(!setup)
                {
                  x = gfx_xpos();
                  y = gfx_ypos();
                } else {
                  // click colors for player zeron and one, and choose not playing for others
                  if(setuprun < 2)
                  {
                    x = (4+setuprun)*xsize/20 + 1;
                    y = (8.5 + 2.6*setuprun)*ysize/20 + 1;
                  } else {
                    x = (10*xsize)/20 + 1;
                    y = (8.5+2.6*setuprun)*ysize/20 + 1;
                  }
                }

                // check if its on the play button
                  if( x >= 13*xsize/20  &&
                      x <= 15*xsize/20  &&
                      y >= 12*ysize/20  &&
                      y <= 12*ysize/20 + xsize/20)
                    {
                      // count how many players are playing and return it
                        int n = 0;
                        for(int p = 0; p <= 3; p++)
                        {
                          if(players[p].getPlaying())
                            n++;
                        }
                      return n;
                    }
                // Run through each player
                  for(int p = 0; p <= 3; p++)
                  {
                    // run through each color square
                      for(int i = 0; i < 6; i++)
                      {
                        // check if mouse click is in the box
                          if( x >= (4+i)*xsize/20                     &&
                              x <= (4+i)*xsize/20 + xsize/20          &&
                              y >= (8.5 + 2.6*p)*ysize/20             &&
                              y <= (8.5 + 2.6*p)*ysize/20 + xsize/20  )
                          {
                            // Set snake to playing
                              players[p].setPlaying(true);

                            // Set snake to to that color
                              players[p].setRed(colors[i][0]);
                              players[p].setGreen(colors[i][1]);
                              players[p].setBlue(colors[i][2]);

                            // erase last white border (by redrawing all squares)
                              // draw color squares
                                for (int j = 0; j < 6; j++)
                                {
                                  // Pick color from array
                                    gfx_color(colors[j][0], colors[j][1], colors[j][2]);
                                  // Draw square
                                    drawSolidSquare((4+j)*xsize/20, (8.5 + 2.6*p)*ysize/20, xsize/20);
                                }

                              // Draw white box with x
                                gfx_color(255,255,255);
                                drawSolidSquare((10)*xsize/20, (8.5 + 2.6*p)*ysize/20, xsize/20);
                                gfx_color(255,0,0);
                                gfx_line(10*xsize/20, (8.5 + 2.6*p)*ysize/20, 10*xsize/20 + xsize/20, (8.5 + 2.6*p)*ysize/20 + xsize/20);
                                gfx_line(10*xsize/20, (8.5 + 2.6*p)*ysize/20 + xsize/20, 10*xsize/20 + xsize/20, (8.5 + 2.6*p)*ysize/20);

                            // Draw a white border w pixels thick
                              gfx_color(255, 255, 255);
                              int w = 3;
                              int x1, y1, length;
                              for(int pix = 0; pix < w; pix++)
                              {
                                x1 = (4+i)*xsize/20 + pix;
                                y1 = (8.5 + 2.6*p)*ysize/20 + pix;
                                length = xsize/20 - 2*pix;

                                gfx_line(x1, y1, x1 + length, y1);
                                gfx_line(x1 + length, y1, x1 + length, y1 + length);
                                gfx_line(x1 + length, y1 + length, x1, y1 + length);
                                gfx_line(x1, y1 + length, x1, y1);
                              }
                      }
                  }

                // check white square, but dont allow number of players < 0
                  // count number of players
                    int currentplayers = 0;
                    for(int p2 = 0; p2 <= 3; p2++)
                   {
                      if(players[p2].getPlaying())
                        currentplayers++;
                    }
                  // check white square if there's enough players
                  if(currentplayers > 2)
                  {
                    if( x >= (10)*xsize/20                     &&
                        x <= (10)*xsize/20 + xsize/20          &&
                        y >= (8.5 + 2.6*p)*ysize/20             &&
                        y <= (8.5 + 2.6*p)*ysize/20 + xsize/20  )
                      {
                        // set snake to not playing
                          players[p].setPlaying(false);

                        // erase white border (by redrawing all squares)
                          for (int j = 0; j < 6; j++)
                          {
                            // Pick color from array
                              gfx_color(colors[j][0], colors[j][1], colors[j][2]);
                            // Draw square
                              drawSolidSquare((4+j)*xsize/20, (8.5 + 2.6*p)*ysize/20, xsize/20);
                          }

                        // draw red border
                          gfx_color(255, 0, 0);
                          int w = 3;
                          int x1, y1, length;
                          for(int pix = 0; pix < w; pix++)
                          {
                            x1 = (10)*xsize/20 + pix;
                            y1 = (8.5 + 2.6*p)*ysize/20 + pix;
                            length = xsize/20 - 2*pix;

                            gfx_line(x1, y1, x1 + length, y1);
                            gfx_line(x1 + length, y1, x1 + length, y1 + length);
                            gfx_line(x1 + length, y1 + length, x1, y1 + length);
                            gfx_line(x1, y1 + length, x1, y1);
                          }
                      }
                  }
              }
            }
         } // ends the if there's a event
	  }
	  // Turn off setup
	    setup = false;
   }
}

void drawSolidSquare(double x, double y, double s)
{
  for(int i = 0; i <= s; i++)
    gfx_line(x, y + i, x + s, y + i);
}

bool endmenu(vector<Snake> players, double xsize, double ysize, int w)
{
  const char * numbers[] = {"0", "1", "2", "3", "4", "5"};
    int x1 = xsize/2 - 150;
    int x2 = xsize/2 + 150;
    gfx_color(50,50,50);
    for(int y = ysize - 10*ysize/12; y < ysize - 4*ysize/12 + 60; y++){
      gfx_line(x1, y, x2, y);
    }

    gfx_color(0,0,0);
    gfx_text(xsize/2 - 8, ysize - 9*ysize/12, "END GAME");

    gfx_text(xsize/2 - 100, ysize - 8.5*ysize/12, "WINNER:");
    gfx_color(players[w].getRed(), players[w].getGreen(), players[w].getBlue());
    gfx_text(xsize/2, ysize - 8.5*ysize/12, "PLAYER"); //winner player
    gfx_text(xsize/2 + 5*12, ysize - 8.5*ysize/12, numbers[w]);

    gfx_color(0,0,0);
    gfx_text(xsize/2 - 100, ysize - 7.5*ysize/12, "PLAYER");
    gfx_text(xsize/2, ysize - 7.5*ysize/12, "SCORE");

    if(players[0].getPlaying())
    {
      gfx_color(players[0].getRed(), players[0].getGreen(), players[0].getBlue());
      gfx_text(xsize/2 - 100, ysize - 7*ysize/12, "PLAYER 0:");
      gfx_text(xsize/2, ysize - 7*ysize/12, numbers[players[0].getWins()]);
    }

    if(players[1].getPlaying())
    {
      gfx_color(players[1].getRed(), players[1].getGreen(), players[1].getBlue());
      gfx_text(xsize/2 - 100, ysize - 6.5*ysize/12, "PLAYER 1:");
      gfx_text(xsize/2, ysize - 6.5*ysize/12, numbers[players[1].getWins()]);
    }

    if(players[2].getPlaying())
    {
      gfx_color(players[2].getRed(), players[2].getGreen(), players[2].getBlue());
      gfx_text(xsize/2 - 100, ysize - 6*ysize/12, "PLAYER 2:");
      gfx_text(xsize/2, ysize - 6*ysize/12, numbers[players[2].getWins()]);
    }

    if(players[3].getPlaying())
    {
      gfx_color(players[3].getRed(), players[3].getGreen(), players[3].getBlue());
      gfx_text(xsize/2 - 100, ysize - 5.5*ysize/12, "PLAYER 3:");
      gfx_text(xsize/2, ysize - 5.5*ysize/12, numbers[players[3].getWins()]);
    }

    //draw box
    gfx_color(0, 0, 0); // black
    gfx_text(xsize/2 - 20, ysize - 4.5*ysize/12, "PLAY AGAIN");

    gfx_line(xsize/2 - 30, ysize - 4.5*ysize/12 + 10, xsize/2 + 50, ysize - 4.5*ysize/12 + 10);
    gfx_line(xsize/2 - 30, ysize - 4.5*ysize/12 - 15, xsize/2 + 50, ysize - 4.5*ysize/12 - 15);

    gfx_line(xsize/2 + 50, ysize - 4.5*ysize/12 + 10, xsize/2 + 50, ysize - 4.5*ysize/12 - 15);
    gfx_line(xsize/2 - 30, ysize - 4.5*ysize/12 + 10, xsize/2 - 30, ysize - 4.5*ysize/12 - 15);

    gfx_text(xsize/2 + 4, ysize - 4.5*ysize/12 + 40, "EXIT");

    gfx_line(xsize/2 - 30, ysize - 4.5*ysize/12 + 50, xsize/2 + 50, ysize - 4.5*ysize/12 + 50);
    gfx_line(xsize/2 - 30, ysize - 4.5*ysize/12 + 25, xsize/2 + 50, ysize - 4.5*ysize/12 + 25);
    gfx_line(xsize/2 + 50, ysize - 4.5*ysize/12 + 50, xsize/2 + 50, ysize - 4.5*ysize/12 + 25);
    gfx_line(xsize/2 - 30, ysize - 4.5*ysize/12 + 50, xsize/2 - 30, ysize - 4.5*ysize/12 + 25);

  while(true)
  {

    if(gfx_event_waiting()){
      char c = gfx_wait();
        if(c == 1){
          int x = gfx_xpos();
          int y = gfx_ypos();
          // play again button
          if((x >= xsize/2 - 30) && (x <= xsize/2 + 50) && (y >= ysize - 4.5*ysize/12 - 15) && (y <= ysize - 4.5*ysize/12 + 10)){
            return true;
          }
          // exit button
          if((x >= xsize/2 - 30) && (x <= xsize/2 + 50) && (y >= ysize - 4.5*ysize/12 + 25) && (y <= ysize - 4.5*ysize/12 + 50)){
            return false;
          }
        }
       if(c == 27)
         return false;
       if(c == '1')
         return true;
    }
  }


}

void drawtitle(int xsize, int ysize, int colors[][3])
{
  // this function draws CC - TRON

  // creates "pixel" size
    int x = 0.0187*xsize;

  // draw 1st C
    // set color
      gfx_color(colors[0][0], colors[0][1], colors[0][2]);
    // draw left side
      for(int i = 0; i < 7; i++)
        drawSolidSquare(8*x, (3+i)*x, x);
    // draw top
      for(int i = 0; i < 4; i++)
        drawSolidSquare((9+i)*x, 3*x, x);
    // draw bottom
      for(int i = 0; i < 4; i++)
        drawSolidSquare((9+i)*x, 9*x, x);

  // draw 2nd C
    // set color
      gfx_color(colors[1][0], colors[1][1], colors[1][2]);
    // draw left side
      for(int i = 0; i < 7; i++)
        drawSolidSquare(14*x, (3+i)*x, x);
    // draw top
      for(int i = 0; i < 4; i++)
        drawSolidSquare((15+i)*x, 3*x, x);
    // draw bottom
      for(int i = 0; i < 4; i++)
        drawSolidSquare((15+i)*x, 9*x, x);

  // draw dash
    gfx_color(115,115,115);//255, 255, 255);
    for(int i = 0; i < 2; i++)
      drawSolidSquare((20+i)*x, 6*x, x);

  // draw T
    // set color
      gfx_color(colors[2][0], colors[2][1], colors[2][2]);
    // draw top
      for(int i = 0; i < 5; i++)
        drawSolidSquare((23+i)*x, 3*x, x);
    // draw 'trunk'
      for(int i = 0; i < 6; i++)
        drawSolidSquare(25*x, (4+i)*x, x);

  // draw R
    // set color
      gfx_color(colors[3][0], colors[3][1], colors[3][2]);
    // draw left
      for(int i = 0; i < 7; i++)
        drawSolidSquare(29*x, (3+i)*x, x);
    // draw top
      for(int i = 0; i < 4; i++)
        drawSolidSquare((30+i)*x, 3*x, x);
    // draw bottom of loop
      for(int i = 0; i < 4; i++)
        drawSolidSquare((30+i)*x, 6*x, x);
    // draw right of loop
      for(int i = 0; i < 2; i++)
        drawSolidSquare(33*x, (4+i)*x, x);
    // draw diagonoal
      for(int i = 0; i < 3; i++)
        drawSolidSquare((31+i)*x, (7+i)*x, x);
  // draw O
    // set color
      gfx_color(colors[4][0], colors[4][1], colors[4][2]);
    // draw top
      for(int i = 0; i < 5; i++)
        drawSolidSquare((35+i)*x, 3*x, x);
    // draw botttom
      for(int i = 0; i < 5; i++)
        drawSolidSquare((35+i)*x, 9*x, x);
    // draw left
      for(int i = 0; i < 5; i++)
        drawSolidSquare(35*x, (4+i)*x, x);
    // draw right
      for(int i = 0; i < 5; i++)
        drawSolidSquare(39*x, (4+i)*x, x);
  // draw N
    // set color
      gfx_color(colors[5][0], colors[5][1], colors[5][2]);
    // draw left
      for(int i = 0; i < 7; i++)
        drawSolidSquare(41*x, (3+i)*x, x);
    // draw right
      for(int i = 0; i < 7; i++)
        drawSolidSquare(45*x, (3+i)*x, x);
    // draw diagonal
      // top left of diagonal
        drawSolidSquare(42*x, 4*x, x);
      // middle diagonal
        for(int i = 0; i < 3; i++)
          drawSolidSquare(43*x, (5+i)*x, x);
      // bottom right of diagonal
        drawSolidSquare(44*x, 8*x, x);
}

