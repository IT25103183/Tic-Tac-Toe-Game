#include <stdio.h>

char board[3][3];

void boardprint()
{
	printf(" --- --- --- \n");
	for(int i=0;i<3;i++)
	{
		printf("| %c | %c | %c |\n", board[i][0], board[i][1], board[i][2]);
		printf(" --- --- --- \n");
	}
}

char user1()
{
	char n;
	printf("Enter User 1: ");
	scanf(" %c", &n);
	return n;
}

char user2()
{
	char n;
        printf("Enter User 2: ");
        scanf(" %c", &n);
	return n;
}

void check(char n,char input)
{
	int i,j;
	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
		{
			if(board[i][j] == n)
			{
				board[i][j] = input;
				return;
			}
		}
	}
}

int winx()
{	
	if(board[0][0]=='X' && board[0][1]=='X' && board[0][2]=='X')
	{
		return 1;
	}
	else if(board[1][0]=='X' && board[1][1]=='X' && board[1][2]=='X')
	{
		return 1;
	}
	else if(board[2][0]=='X' && board[2][1]=='X' && board[2][2]=='X')
	{
		return 1;
	}
	else if(board[0][0]=='X' && board[1][0]=='X' && board[2][0]=='X')
	{
		return 1;
	}
	else if(board[0][1]=='X' && board[1][1]=='X' && board[2][1]=='X')
	{
		return 1;
	}
	else if(board[0][2]=='X' && board[1][2]=='X' && board[2][2]=='X')
	{
		return 1;
	}
	else if(board[0][0]=='X' && board[1][1]=='X' && board[2][2]=='X')
	{
		return 1;
	}
	else if(board[0][2]=='X' && board[1][1]=='X' && board[2][0]=='X')
	{
		return 1;
	}
	return 0;
}

int wino()
{
	if(board[0][0]=='O' && board[0][1]=='O' && board[0][2]=='O')
	{
		return 1;
	}
	else if(board[1][0]=='O' && board[1][1]=='O' && board[1][2]=='O')
	{
		return 1;
	}
	else if(board[2][0]=='O' && board[2][1]=='O' && board[2][2]=='O')
	{
		return 1;
	}
	else if(board[0][0]=='O' && board[1][0]=='O' && board[2][0]=='O')
	{
		return 1;
	}
	else if(board[0][1]=='O' && board[1][1]=='O' && board[2][1]=='O')
	{
		return 1;
	}
	else if(board[0][2]=='O' && board[1][2]=='O' && board[2][2]=='O')
	{
		return 1;
	}
	else if(board[0][0]=='O' && board[1][1]=='O' && board[2][2]=='O')
	{
		return 1;
	}
	else if(board[0][2]=='O' && board[1][1]=='O' && board[2][0]=='O')
	{
		return 1;
	}
	return 0;
}

int main()
{
	int i,j;
	int num = 1;
	int y = 0;
	char m;
	
	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
		{
			board[i][j] = '0' + num;
			num++;
		}
	}

	boardprint();

	for(i=0;i<9;i++)
	{
		if(i % 2 == 0)
		{
			m = user1();
			check(m,'X');
			boardprint();
		}
		else
		{			
			m = user2();
			check(m,'O');
			boardprint();
		}
		
		y = winx();

		if(y==1)
		{
			printf("PLAYER 1 WINS\n");
			break;
		}

		y = wino();
		
		if(y==1)
		{
			printf("PLAYER 2 WINS\n");
			break;
		}
		if(i == 8)
		{
			printf("DRAW!\n");
		}
	}

	return 0;
}
