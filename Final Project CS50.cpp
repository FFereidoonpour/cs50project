// A Minesweeper project
// Fatemeh Fereidoonpour

#include <iostream>
#include<bits/stdc++.h>
using namespace std;
 
#define BEGINNER 1
#define INTERMEDIATE 2
#define ADVANCED 3
#define player 4
#define MAXSIDE 25
#define MAXMINES 99
#define MOVESIZE 526 // cells whithout mines
 
int SIDE ;
int Soton;
int Radif;
int MINES ;

//to understand that cell is valid or not
bool isValid(int row, int col)
{
    return (row >= 0) && (row < Radif) &&
           (col >= 0) && (col < Soton);
}
 
//to check that cell has a mine or not
bool isMine (int row, int col, char board[][MAXSIDE])
{
    if (board[row][col] == '*')
        return (true);
    else
        return (false);
}
 
//get move from user
void makeMove(int *x, int *y)
{
    printf("Enter your move, column) -> ");
    scanf("%d", y);
    printf("Enter your move, row) -> ");
    scanf("%d", x);
    return;
}
 
//print play board
void printBoard(char myBoard[][MAXSIDE])
{
    int i, j;
 
    printf ("    ");
 
    for (i=0; i<Soton; i++)
        printf ("%.2d ", i);
 
    printf ("\n\n");
 
    for (i=0; i<Soton; i++)
    {
        printf ("%.2d   ", i);
 
        for (j=0; j<Radif; j++)
            printf ("%c  ", myBoard[i][j]);
        printf ("\n");
    }
    return;
}

//count near mines 1 to 8
int countAdjacentMines(int row, int col, int mines[][2], char realBoard[][MAXSIDE])
{
    // Only process this cells if they are valid ones
    int i;
    int count = 0;
        if (isValid (row-1, col) == true) //(North)
        {
               if (isMine (row-1, col, realBoard) == true)
               count++;
        }
        if (isValid (row+1, col) == true) //(South)
        {
               if (isMine (row+1, col, realBoard) == true)
               count++;
        }
        if (isValid (row, col+1) == true)//(East)
        {
            if (isMine (row, col+1, realBoard) == true)
               count++;
        }
        if (isValid (row, col-1) == true)//(West)
        {
               if (isMine (row, col-1, realBoard) == true)
               count++;
        }
        if (isValid (row-1, col+1) == true)//(North-East)
        {
            if (isMine (row-1, col+1, realBoard) == true)
               count++;
        }
        if (isValid (row-1, col-1) == true)//(North-West)
        {
             if (isMine (row-1, col-1, realBoard) == true)
               count++;
        }
        if (isValid (row+1, col+1) == true) //(South-East)
        {
               if (isMine (row+1, col+1, realBoard) == true)
               count++;
        }
        if (isValid (row+1, col-1) == true) //(South-West)
        {
            if (isMine (row+1, col-1, realBoard) == true)
               count++;
        }
 
    return (count);
}
 
//recursive func for playing game
bool playMinesweeperUtil(char myBoard[][MAXSIDE], char realBoard[][MAXSIDE], int mines[][2], int row, int col, int *movesLeft)
{
 
   
    if (myBoard[row][col] != '-')
        return (false);
 
    int i, j;
 
    //you chose mine and going to lose
	if (realBoard[row][col] == '*')
    {
        myBoard[row][col]='*';
 
        for (i=0; i<MINES; i++)
            myBoard[mines[i][0]][mines[i][1]]='*';
 
        printBoard (myBoard);
        printf ("\nYou lost!\a\n");
        return (true) ;
    }
 
    else
     {
        // Calculate adjacent mines and write it
        int count = countAdjacentMines(row, col, mines, realBoard);
        (*movesLeft)--;
 
        myBoard[row][col] = count + '0';
 
        if (!count)
        {
            // Only process this cells if they are valid ones
            if (isValid (row-1, col) == true)//(North)
            {
                   if (isMine (row-1, col, realBoard) == false)
                   playMinesweeperUtil(myBoard, realBoard, mines, row-1, col, movesLeft);
            }
            if (isValid (row+1, col) == true)//(South)
            {
                   if (isMine (row+1, col, realBoard) == false)
                    playMinesweeperUtil(myBoard, realBoard, mines, row+1, col, movesLeft);
                    }
            if (isValid (row, col+1) == true)//(East)
            {
                if (isMine (row, col+1, realBoard) == false)
                    playMinesweeperUtil(myBoard, realBoard, mines, row, col+1, movesLeft);
            }
            if (isValid (row, col-1) == true)//(West)
            {
                   if (isMine (row, col-1, realBoard) == false)
                    playMinesweeperUtil(myBoard, realBoard, mines, row, col-1, movesLeft);
            }
            if (isValid (row-1, col+1) == true)//(North-East)
            {
                if (isMine (row-1, col+1, realBoard) == false)
                    playMinesweeperUtil(myBoard, realBoard, mines, row-1, col+1, movesLeft);
            }
            if (isValid (row-1, col-1) == true)//(North-West)
            {
                 if (isMine (row-1, col-1, realBoard) == false)
                    playMinesweeperUtil(myBoard, realBoard, mines, row-1, col-1, movesLeft);
            }
            if (isValid (row+1, col+1) == true)//(South-East)
            {
                 if (isMine (row+1, col+1, realBoard) == false)
                    playMinesweeperUtil(myBoard, realBoard, mines, row+1, col+1, movesLeft);
            }
            if (isValid (row+1, col-1) == true)//(South-West)
            {
                if (isMine (row+1, col-1, realBoard) == false)
                    playMinesweeperUtil(myBoard, realBoard, mines, row+1, col-1, movesLeft);
            }
        }
 
        return (false);
    }
}
 
//place mines randomly
void placeMines(int mines[][2], char realBoard[][MAXSIDE])
{
    bool mark[MAXSIDE*MAXSIDE];
 
    memset (mark, false, sizeof (mark));
 
    //continue untilall mines create
	for (int i=0; i<MINES; )
     {
        int random = rand() % (Soton*Radif);
        int x = random / Radif;
        int y = random % Soton;
 
        //add mine if cell is empty yet
		if (mark[random] == false)
        {
            mines[i][0]= x;//row index
            mines[i][1] = y;//column index
 
            // Place the mine
            realBoard[mines[i][0]][mines[i][1]] = '*';
            mark[random] = true;
            i++;
        }
    }
 
    return;
}

//initialise the game
void initialise(char realBoard[][MAXSIDE], char myBoard[][MAXSIDE])
{
    // Initiate the random number generator because the same configuration doesn't arises
    srand(time (NULL));
 
    //assign all cells as mine free
	for (int i=0; i<Soton; i++)
    {
        for (int j=0; j<Radif; j++)
        {
            myBoard[i][j] = realBoard[i][j] = '-';
        }
    }
 
    return;
}
 
// A Function to cheat by revealing where the mines are
// placed
void cheatMinesweeper (char realBoard[][MAXSIDE])
{
    printf ("The mines locations are-\n");
    printBoard (realBoard);
    return;
}
 
//replace mine and put into vacant space
void replaceMine (int row, int col, char board[][MAXSIDE])
{
    for (int i=0; i<Soton; i++)
    {
        for (int j=0; j<Radif; j++)
            {
                if (board[i][j] != '*')//find first location which doesnt have a mine and put one
                {
                    board[i][j] = '*';
                    board[row][col] = '-';
                    return;
                }
            }
    }
    return;
}
 
//for playing game
void playMinesweeper ()
{
    //at first the game isnt over
	bool gameOver = false;
 
    //actual board and my board
	char realBoard[MAXSIDE][MAXSIDE], myBoard[MAXSIDE][MAXSIDE];
 
    int movesLeft = Soton * Radif - MINES, x, y;
    // stores (x,y) coordinates of all mines.
	int mines[MAXMINES][2]; 
 
      initialise (realBoard, myBoard);
 
    //place mines randomly
	placeMines (mines, realBoard);
 
     
    /*
     cheatMinesweeper(realBoard);
//if you want to cheat just uncomment this line and it will show you real board
*/
 
    int currentMoveIndex = 0;
    while (gameOver == false)
     {
        printf ("Current Status of Board : \n");
        printBoard (myBoard);
        makeMove (&x, &y);
 
        //first move is always safe
		if (currentMoveIndex == 0)
        {
            //if it has mine we remove it from that location
			if (isMine (x, y, realBoard) == true)
                replaceMine (x, y, realBoard);
        }
 
        currentMoveIndex ++;
 
        gameOver = playMinesweeperUtil (myBoard, realBoard, mines, x, y, &movesLeft);
 
        if ((gameOver == false) && (movesLeft == 0))
         {
            printf ("\nYou won !\a\n");
            gameOver = true;
         }
    }
    return;
}
 
//choose its level
void chooseDifficultyLevel ()
{
    int level;
 
    printf ("Enter the Difficulty Level\n");
    printf ("Press 1 for BEGINNER (9 * 9 Cells and 10 Mines)\n");
    printf ("Press 2 for INTERMEDIATE (16 * 16 Cells and 40 Mines)\n");
    printf ("Press 3 for ADVANCED (24 * 24 Cells and 99 Mines)\n");
    printf ("press 4 for player choice (you have to choose it by yourself)\n");
 
    scanf ("%d", &level);
 
    if (level == BEGINNER)
    {
        Soton = 9;
        Radif = 9;
        MINES = 10;
    }
 
    if (level == INTERMEDIATE)
    {
        
        Soton = 16;
        Radif = 16;
        MINES = 40;
    }
 
    if (level == ADVANCED)
    {
        Soton = 24;
        Radif = 24;
        MINES = 99;
    }
   
    if (level == player)
    {
    int a,b,c;
    printf ("please enter side 25 or less.\n\n");
    printf ("\t\tenter Soton :\n\n");
    scanf ("%d",&a);
    printf ("\t\tenter Radif :\n");
    scanf ("%d",&b);
    printf ("\t\tenter MINES :\n");
    scanf ("%d",&c);
    Soton = a;
    Radif = b;
    MINES = c;
   
}
 
    return;
}
 
int main()
{
    chooseDifficultyLevel ();
 
    playMinesweeper ();
 
    return (0);
}
