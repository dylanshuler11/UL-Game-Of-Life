#include <stdio.h>
#include <stdlib.h>
#include "gol.h"

int board = 0b0011100010000000;
int copy_board = 0b0011100010000000;

void main()
{
	printf("Generation 0:\n");
	print_board();
	short i = 0;
	for(i = 0; i < 1; i++)
	{
		evolve();
		printf("Generation %d:\n",i+1);
		print_board();
	}
}

void evolve()
{
	short x, y, count;
	for(x = 0; x < 5; x++)
	{
		for(y = 0; y < 5; y++)
		{
			count = count_neighbors(x,y);
			if(count == 3 && get_cell_value(x,y) == 0)
			{
				copy_board |= (1<<5*x+y);
			}
			else if((count < 2 || count > 3) && get_cell_value(x,y) == 1)
			{
				copy_board &= ~(1<<5*x+y);
			}
		}
	}
	board = copy_board;
}

short count_neighbors(short x, short y)
{
	short count = 0;
	count += get_cell_value(x-1,y-1);
	count += get_cell_value(x-1,y);
	count += get_cell_value(x-1,y+1);
	count += get_cell_value(x,y-1);
	count += get_cell_value(x,y+1);
	count += get_cell_value(x+1,y-1);
	count += get_cell_value(x+1,y);
	count += get_cell_value(x+1,y+1);
	return count;
}

short get_cell_value(short x, short y)
{
	//ensure valid coordinates
	if(x >= 0 && x <= 4 && y >= 0 && y <= 4)
	{
		return (board & (1 << x*5+y)) >> x*5+y;
	}
	else
	{
		return 0;
	}
}

void print_board()
{
	short x,y;
	for(x = 0; x < 5; x++)
	{
		for(y = 0; y < 5; y++)
		{
			if(get_cell_value(x,y) == 1)
			{
				printf("*");
			}
			else
			{
				printf(" ");
			}
		}
		printf("\n");
	}
}