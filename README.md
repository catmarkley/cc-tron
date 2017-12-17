# cc-tron

Created By: Catherine Markley and Christopher Foley  
Game: CC-TRON, similar to BM-TRON but renamed CC for "Chris and Catherine"  
Date: 12/9/17  

## Rules of the Game:
* For our final project, we re-created a version of BM-TRON, a game similar to snake. This is a multiplayer game where each player uses a different set of four keys to control their snake. The snakes can be moved up, down, left, or right but cannot run into each other or run off the sides of the board. When the program is first run, the start menu appears. This allows the users to choose the colors of their snake, the number of players, and click the start button when ready. Next to each player choice there is a list of colors and specified keys for each player. Once the start button is clicked, the specified number of players appear on the board in a line in their specified colors. Each player must then type a key to specify their initial direction. Once all players have pressed a key, the snakes start to move. Each player can change the direction of their snake at any time by pressing their specified up, down, left, or right key. To end the round, all players except for one must die. The winning player gets a point, and whichever player gets five points first will win the game. If all the alive snakes on the board die at the same time, no player gets a point for that round. Once a player wins the game, the end menu is displayed. This shows the winning player and the final scores of every snake. It also includes “Play Again” and “Exit” buttons, which bring the user back to the start menu or exit the program. At any point in the program, if the user hits the escape key, the program will terminate. 
* In order for the best user experience, we suggest running the program on a student machine. This allows the grid to load faster for each round which allows the program to run faster. We also suggest that the user does not choose the same colors for different snakes because it might confuse the user. We left this option up to the user.


## Menu Rules:
The start menu displays a set of 7 different options for each player. These options include red, orange, yellow, green, blue, purple, and a white box with a red X to specify that a player is not active. The user must choose at least two players to be active in order to play the game. We designed the program so it is impossible to start the game with less than two players. The four different sets of keys used are the arrows (Player 0), WASD (Player 1), YGHJ (Player 2), and PL;’ (Player 3). The user can choose any combination of 2, 3, or 4 of these players. 


## Description of the program:
* The program is organized into three main areas: the main class, the board class, and the snake class. The board class basically sets up an array of cells for the board that the snake is able to travel on. These cells can be marked as taken or empty depending on whether any snake occupies a cell. The board class also has a clear function which sets all the cells back to not taken.
* The snake class allows the program to create a snake object for each player. Each snake includes attributes such as the current direction, position, color, whether it is alive or dead, and its number of wins.
* The main class includes the files for both the board class and the snake class. After the set up of variables and the graphics window at the beginning of the program, the main class uses three different while loops to determine the start and end of each round, game, and the running of the program. 
