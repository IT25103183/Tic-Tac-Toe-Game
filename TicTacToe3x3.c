#include <stdio.h>

char c[9];

void board()
{
	printf(" --- --- --- \n");
	printf("| %c | %c | %c |\n", c[0], c[1], c[2]);
	printf(" --- --- --- \n");
	printf("| %c | %c | %c |\n", c[3], c[4], c[5]);
	printf(" --- --- --- \n");
	printf("| %c | %c | %c |\n", c[6], c[7], c[8]);
	printf(" --- --- --- \n");
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
	int i;
	for(i=0;i<9;i++)
	{
		if(c[i] == n)
		{
			c[i] = input;
			break;
		}
	}
}

int winx()
{	
	if(c[0]=='X' && c[1]=='X' && c[2]=='X')
	{
		return 1;
	}
	else if(c[3]=='X' && c[4]=='X' && c[5]=='X')
	{
		return 1;
	}
	else if(c[6]=='X' && c[7]=='X' && c[8]=='X')
	{
		return 1;
	}
	else if(c[0]=='X' && c[3]=='X' && c[6]=='X')
	{
		return 1;
	}
	else if(c[1]=='X' && c[4]=='X' && c[7]=='X')
	{
		return 1;
	}
	else if(c[2]=='X' && c[5]=='X' && c[8]=='X')
	{
		return 1;
	}
	else if(c[1]=='X' && c[4]=='X' && c[8]=='X')
	{
		return 1;
	}
	else if(c[2]=='X' && c[4]=='X' && c[6]=='X')
	{
		return 1;
	}
}

int wino()
{
	if(c[0]=='O' && c[1]=='O' && c[2]=='O')
	{
		return 0;
	}
	else if(c[3]=='O' && c[4]=='O' && c[5]=='O')
	{
		return 0;
	}
	else if(c[6]=='O' && c[7]=='O' && c[8]=='O')
	{
		return 0;
	}
	else if(c[0]=='O' && c[3]=='O' && c[6]=='O')
	{
		return 0;
	}
	else if(c[1]=='O' && c[4]=='O' && c[7]=='O')
	{
		return 0;
	}
	else if(c[2]=='O' && c[5]=='O' && c[8]=='O')
	{
		return 0;
	}
	else if(c[0]=='O' && c[4]=='O' && c[8]=='O')
	{
		return 0;
	}
	else if(c[2]=='O' && c[4]=='O' && c[6]=='O')
	{
		return 0;
	}
}

int main()
{
	int i;
	int y = 0;
	char m;
	
	for(i=0;i<9;i++)
	{
		c[i] = i + '1';
	}

	board();

	for(i=0;i<9;i++)
	{
		if(i % 2 == 0)
		{
			m = user1();
			check(m,'X');
			board();
		}
		else
		{			
			m = user2();
			check(m,'O');
			board();
		}
		
		y = winx();

		if(y==1)
		{
			printf("PLAYER 1 WINS\n");
			break;
		}

		y = wino();
		
		if(y==0)
		{
			printf("PLAYER 2 WINS\n");
			break;
		}
	}

	return 0;
}
