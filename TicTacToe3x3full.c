#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char board[3][3];
int numPlayers;
char symbols[3];
int playerTypes[3];
int currentPlayer;
int movesCount;
FILE *logFile;

void initializeGame();
void displayBoard();
void getPlayerInput(int *row, int *col);
int validateMove(int row, int col);
void makeMove(int row, int col);
int checkWin();
int checkDraw();
void computerMove();
void logMove(int row, int col);
void setupGame();
void playGame();

void initializeGame()
{
	int i, j;
	for (i = 0; i < 3; i++)
	{	
		for (j = 0; j < 3; j++)
		{
			board[i][j] = ' ';
		}
	}
	movesCount = 0;
	currentPlayer = 0;
	
	logFile = fopen("game_log.txt", "w");
	if (logFile != NULL) 
	{
		fprintf(logFile, "=== TIC-TAC-TOE GAME LOG ===\n");
		fprintf(logFile, "Board Size: 3 x 3\n");
		fprintf(logFile, "Number of Players: %d\n\n", numPlayers);
	}
}

void displayBoard()
{
	int i, j;
	
	printf("\n");
	
	printf("     0   1   2\n");
	printf("   +---+---+---+\n");
	
	for (i = 0; i < 3; i++)
	{
		printf(" %d ", i);
		
		for (j = 0; j < 3; j++)
		{
			printf("| %c ", board[i][j]);
		}
		printf("|\n");
		printf("   +---+---+---+\n");
	}
	printf("\n");
}

void getPlayerInput(int *row, int *col)
{
	printf("Player %c's turn\n", symbols[currentPlayer]);
	printf("Enter row (0-2): ");
	scanf("%d", row);
	printf("Enter column (0-2): ");
	scanf("%d", col);
}

int validateMove(int row, int col)
{
	if (row < 0 || row > 2 || col < 0 || col > 2)
	{
		printf("Invalid position! Please enter values between 0 and 2.\n");
		return 0;
	}
	
	if (board[row][col] != ' ')
	{
		printf("Cell already occupied! Choose another position.\n");
		return 0;
	}
	
	return 1;
}

void makeMove(int row, int col)
{
	board[row][col] = symbols[currentPlayer];
	movesCount++;
	logMove(row, col);
}

int checkWin()
{
	int i;
	char symbol = symbols[currentPlayer];
	
	for (i = 0; i < 3; i++)
	{
		if (board[i][0] == symbol && board[i][1] == symbol && board[i][2] == symbol)
		{
			return 1;
		}
	}
	
	for (i = 0; i < 3; i++)
	{
		if (board[0][i] == symbol && board[1][i] == symbol && board[2][i] == symbol)
		{
			return 1;
		}
	}
	
	if (board[0][0] == symbol && board[1][1] == symbol && board[2][2] == symbol)
	{
		return 1;
	}
	
	if (board[0][2] == symbol && board[1][1] == symbol && board[2][0] == symbol)
	{
		return 1;
	}
	
	return 0;
}

int checkDraw()
{
	if (movesCount == 9) 
	{
		return 1;
	}
	
	return 0;
}

void computerMove()
{
	int row, col;
	int validMove = 0;
    
	printf("Computer (%c) is thinking...\n", symbols[currentPlayer]);
	
	while (!validMove) 
	{
		row = rand() % 3;
		col = rand() % 3;
		
		if (board[row][col] == ' ')
		{
			validMove = 1;
		}
	}
	
	printf("Computer places at position (%d, %d)\n", row, col);
	makeMove(row, col);
}

void logMove(int row, int col)
{
	if (logFile != NULL)
	{
		fprintf(logFile, "Move %d: Player %c -> (%d, %d)\n",movesCount, symbols[currentPlayer], row, col);
		fprintf(logFile, "Board State:\n");
		
		int i, j;
		
		for (i = 0; i < 3; i++)
		{
			for (j = 0; j < 3; j++)
			{
				fprintf(logFile, "[%c]", board[i][j]);
			}
			
			fprintf(logFile, "\n");
		}
		
		fprintf(logFile, "\n");
	}
}

void setupGame()
{
	int choice;
	
	printf("\n=== TIC-TAC-TOE GAME (3x3) ===\n\n");
	printf("Select Game Mode:\n");
	printf("1. Two Players (Human vs Human)\n");
	printf("2. Single Player (Human vs Computer)\n");
	printf("3. Three Players\n");
	printf("Enter choice (1-3): ");
	scanf("%d", &choice);
	
	if (choice == 1)
	{
		numPlayers = 2;
		symbols[0] = 'X';
		symbols[1] = 'O';
		playerTypes[0] = 0;
		playerTypes[1] = 0;
		printf("\nMode: Human vs Human\n");
	}
	else if (choice == 2)
	{
		numPlayers = 2;
		symbols[0] = 'X';
		symbols[1] = 'O';
		playerTypes[0] = 0;
		playerTypes[1] = 1;
		printf("\nMode: Human vs Computer\n");
	}
	else
	{
		numPlayers = 3;
		symbols[0] = 'X';
		symbols[1] = 'O';
		symbols[2] = 'Z';
		
		printf("\nPlayer Configuration:\n");
		printf("Player 1 (X): Human\n");
		printf("Player 2 (O) - Human(0) or Computer(1)? ");
		scanf("%d", &playerTypes[1]);
		
		printf("Player 3 (Z) - Human(0) or Computer(1)? ");
		scanf("%d", &playerTypes[2]);
		
		playerTypes[0] = 0;
		
		printf("\nMode: Three Players\n");
	}
	
	srand(time(NULL));
}

void playGame()
{
	int row, col;
	int gameOver = 0;
	
	initializeGame();
	
	printf("\nGame Started!\n");
	displayBoard();
	
	while (!gameOver)
	{
		if (playerTypes[currentPlayer] == 0)
		{
			do
			{
				getPlayerInput(&row, &col);
			} while (!validateMove(row, col));
			
			makeMove(row, col);
		} 
		
		else
		{
			computerMove();
		}
		
		displayBoard();
		
		if (checkWin())
		{
			printf("*** Player %c WINS! ***\n", symbols[currentPlayer]);
			
			if (logFile != NULL)
			{
				fprintf(logFile, "GAME OVER: Player %c WINS!\n", symbols[currentPlayer]);
			}
			
			gameOver = 1;
		}
		
		else if (checkDraw())
		{
			printf("*** GAME DRAW! ***\n");
			if (logFile != NULL)
			{
				fprintf(logFile, "GAME OVER: DRAW!\n");
			}
			
			gameOver = 1;
		}
		
		else 
		{
			currentPlayer = (currentPlayer + 1) % numPlayers;
		}
	}
	
	if (logFile != NULL)
	{
		fclose(logFile);
	}
}

int main()
{
	char playAgain;
	do
	{
		setupGame();
		playGame();
        
		printf("\nDo you want to play again? (y/n): ");
		scanf(" %c", &playAgain);
	} while (playAgain == 'y' || playAgain == 'Y');
	
	printf("\nThank you for playing Tic-Tac-Toe!\n");
	
	return 0;
}
