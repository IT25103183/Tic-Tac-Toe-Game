#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct
{
    char **board;
    int size;
    int numPlayers;
    char symbols[3];
    int playerTypes[3];
    int currentPlayer;
    int movesCount;
    FILE *logFile;
} GameState;

void initializeGame(GameState *game);
void displayBoard(GameState *game);
void getPlayerInput(GameState *game, int *row, int *col);
int validateMove(GameState *game, int row, int col);
void makeMove(GameState *game, int row, int col);
int checkWin(GameState *game);
int checkDraw(GameState *game);
void computerMove(GameState *game);
void logMove(GameState *game, int row, int col);
void freeBoard(GameState *game);
void setupGame(GameState *game);
void playGame(GameState *game);

void initializeGame(GameState *game)
{
	int i, j;
	
	game->board = (char **)malloc(game->size * sizeof(char *));
	
	for (i = 0; i < game->size; i++)
	{
		game->board[i] = (char *)malloc(game->size * sizeof(char));
	}
	
	for (i = 0; i < game->size; i++)
	{
		for (j = 0; j < game->size; j++)
		{
			game->board[i][j] = ' ';
		}
	}
	
	game->movesCount = 0;
	game->currentPlayer = 0;
	
	game->logFile = fopen("game_log.txt", "w");
	
	if (game->logFile != NULL)
	{
		fprintf(game->logFile, "=== TIC-TAC-TOE GAME LOG ===\n");
		fprintf(game->logFile, "Board Size: %d x %d\n", game->size, game->size);
		fprintf(game->logFile, "Number of Players: %d\n\n", game->numPlayers);
	}
}

void displayBoard(GameState *game)
{
	int i, j;
	
	printf("\n");
	
	printf("   ");
	
	for (i = 0; i < game->size; i++)
	{
		printf("  %d ", i);
	}
	
	printf("\n");
	
	printf("   ");
	
	for (i = 0; i < game->size; i++)
	{
		printf("+---");
	}
	
	printf("+\n");
	
	for (i = 0; i < game->size; i++)
	{
		printf(" %d ", i);
		for (j = 0; j < game->size; j++)
		{
			printf("| %c ", game->board[i][j]);
		}
		
		printf("|\n");
		
		printf("   ");
		
		for (j = 0; j < game->size; j++)
		{
			printf("+---");
		}
		
		printf("+\n");
	}
	
	printf("\n");
}

void getPlayerInput(GameState *game, int *row, int *col)
{
	printf("Player %c's turn\n", game->symbols[game->currentPlayer]);
	printf("Enter row (0-%d): ", game->size - 1);
	scanf("%d", row);
	
	printf("Enter column (0-%d): ", game->size - 1);
	scanf("%d", col);
}

int validateMove(GameState *game, int row, int col)
{
	if (row < 0 || row >= game->size || col < 0 || col >= game->size)
	{
		printf("Invalid position! Please enter values between 0 and %d.\n", game->size - 1);
		return 0;
	}
	
	if (game->board[row][col] != ' ')
	{
		printf("Cell already occupied! Choose another position.\n");
		return 0;
	}
	
	return 1;
}

void makeMove(GameState *game, int row, int col)
{
	game->board[row][col] = game->symbols[game->currentPlayer];
	game->movesCount++;
	logMove(game, row, col);
}

int checkWin(GameState *game)
{
	int i, j, count;
	char symbol = game->symbols[game->currentPlayer];
	
	for (i = 0; i < game->size; i++)
	{
		count = 0;
		
		for (j = 0; j < game->size; j++)
		{
			if (game->board[i][j] == symbol)
			{
				count++;
			}
		}
		
		if (count == game->size)
		{
			return 1;
		}
	}
	
	for (j = 0; j < game->size; j++)
	{
		count = 0;
		
		for (i = 0; i < game->size; i++)
		{
			if (game->board[i][j] == symbol)
			{
				count++;
			}
		}
		
		if (count == game->size)
		{
			return 1;
		}
	}
	
	count = 0;
	
	for (i = 0; i < game->size; i++)
	{
		if (game->board[i][i] == symbol)
		{
			count++;
		}
	}
	
	if (count == game->size)
	{
		return 1;
	}
	
	count = 0;
	
	for (i = 0; i < game->size; i++)
	{
		if (game->board[i][game->size - 1 - i] == symbol)
		{
			count++;
		}
	}
	
	if (count == game->size)
	{
		return 1;
	}
	
	return 0;
}

int checkDraw(GameState *game)
{
	if (game->movesCount == game->size * game->size)
	{
		return 1;
	}
	
	return 0;
}

void computerMove(GameState *game)
{
	int row, col;
	int validMove = 0;
	
	printf("Computer (%c) is thinking...\n", game->symbols[game->currentPlayer]);
	
	while (!validMove)
	{
		row = rand() % game->size;
		col = rand() % game->size;
		
		if (game->board[row][col] == ' ')
		{
			validMove = 1;
		}
	}
	
	printf("Computer places at position (%d, %d)\n", row, col);
	makeMove(game, row, col);
}

void logMove(GameState *game, int row, int col)
{
	if (game->logFile != NULL)
	{
		fprintf(game->logFile, "Move %d: Player %c -> (%d, %d)\n", game->movesCount, game->symbols[game->currentPlayer], row, col);
		fprintf(game->logFile, "Board State:\n");
		
		int i, j;
		
		for (i = 0; i < game->size; i++)
		{
			for (j = 0; j < game->size; j++)
			{
				fprintf(game->logFile, "[%c]", game->board[i][j]);
			}
			
			fprintf(game->logFile, "\n");
		}
		
		fprintf(game->logFile, "\n");
	}
}

void freeBoard(GameState *game)
{
	int i;
	
	for (i = 0; i < game->size; i++)
	{
		free(game->board[i]);
	}
	
	free(game->board);
	
	if (game->logFile != NULL)
	{
		fclose(game->logFile);
	}
}

void setupGame(GameState *game)
{
	int choice;
	
	printf("=== TIC-TAC-TOE GAME ===\n\n");
	
	do
	{
		printf("Enter board size (3-10): ");
		scanf("%d", &game->size);
		
		if (game->size < 3 || game->size > 10)
		{
			printf("Invalid size! Please enter a value between 3 and 10.\n");
		}
	} while (game->size < 3 || game->size > 10);
	
	printf("\nSelect Game Mode:\n");
	printf("1. Two Players (Human vs Human)\n");
	printf("2. Single Player (Human vs Computer)\n");
	printf("3. Three Players\n");
	printf("Enter choice (1-3): ");
	scanf("%d", &choice);
	
	if (choice == 1)
	{
		game->numPlayers = 2;
		game->symbols[0] = 'X';
		game->symbols[1] = 'O';
		game->playerTypes[0] = 0;
		game->playerTypes[1] = 0;
	}
	else if (choice == 2)
	{
		game->numPlayers = 2;
		game->symbols[0] = 'X';
		game->symbols[1] = 'O';
		game->playerTypes[0] = 0;
		game->playerTypes[1] = 1;
	}
	else
	{
		game->numPlayers = 3;
		game->symbols[0] = 'X';
		game->symbols[1] = 'O';
		game->symbols[2] = 'Z';
        
		printf("\nPlayer Configuration:\n");
		printf("Player 1 (X): Human\n");
		printf("Player 2 (O) - Human(0) or Computer(1)? ");
		scanf("%d", &game->playerTypes[1]);
		
		printf("Player 3 (Z) - Human(0) or Computer(1)? ");
		scanf("%d", &game->playerTypes[2]);
		game->playerTypes[0] = 0;
	}
	
	srand(time(NULL));
}

void playGame(GameState *game)
{
	int row, col;
	int gameOver = 0;
	
	initializeGame(game);
	
	printf("\nGame Started!\n");
	
	displayBoard(game);
	
	while (!gameOver)
	{
		if (game->playerTypes[game->currentPlayer] == 0)
		{
			do
			{
				getPlayerInput(game, &row, &col);
			} while (!validateMove(game, row, col));
			
			makeMove(game, row, col);
		}
		else
		{
			computerMove(game);
		}
		
		displayBoard(game);
		
		if (checkWin(game))
		{
			printf("*** Player %c WINS! ***\n", game->symbols[game->currentPlayer]);
			
			if (game->logFile != NULL)
			{
				fprintf(game->logFile, "GAME OVER: Player %c WINS!\n", game->symbols[game->currentPlayer]);
			}
			
			gameOver = 1;
		}
		
		else if (checkDraw(game))
		{
			printf("*** GAME DRAW! ***\n");
			
			if (game->logFile != NULL)
			{
				fprintf(game->logFile, "GAME OVER: DRAW!\n");
			}
			
			gameOver = 1;
		}
		else
		{
			game->currentPlayer = (game->currentPlayer + 1) % game->numPlayers;
		}
	}
	
	freeBoard(game);
}

int main()
{
	GameState game;
	
	char playAgain;
	
	do
	{
		setupGame(&game);
		playGame(&game);
		
		printf("\nDo you want to play again? (y/n): ");
		
		scanf(" %c", &playAgain);
	
	} while (playAgain == 'y' || playAgain == 'Y');
	
	printf("\nThank you for playing Tic-Tac-Toe!\n\n");
	
	return 0;
}

