/*
1.256 
1.240 
1.210 
1.194 
1.210 
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define WIDTH 2048      /* array sizes */
#define HEIGHT 2048

//print matrix
void * print_m(int** tbp)
{
	int i, j;
	for (i = 0; i < WIDTH; i++)
	{
		for (j = 0; j < HEIGHT; j++)
		{
			printf("%d ", tbp[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

int main(int argc, char *argv[]) 
{
	clock_t start = clock();
	int i, j; //counters
	int **src;
	int **dest;

	/* allocate */
	src = malloc(WIDTH * sizeof(int*));
	dest = malloc(WIDTH * sizeof(int*));
	for (i = 0; i < WIDTH; i++) {
		src[i] = malloc(HEIGHT * sizeof(int));
		dest[i] = malloc(HEIGHT * sizeof(int));
	}

	/*  init src  */
	time_t t;
	srand((unsigned)time(&t));
	float x;
	for (i = 0; i < WIDTH; i++) 
	{
		for (j = 0; j < HEIGHT; j++) 
		{
			x = rand() / ((float)RAND_MAX + 1);
			if (x<0.5) 
				src[i][j] = 0;
			else 
				src[i][j] = 1;
		}
	}

	//print_m(src);

	int neighbours = 0;
	int ySHFT = 0;
	int xSHFT = 0;

	for (i = 0; i < WIDTH; i++) 
	{
		for (j = 0; j < HEIGHT; j++) 
		{
			neighbours = 0;
			for (ySHFT = -1; ySHFT <= 1; ySHFT++) 
			{
				for (xSHFT = -1; xSHFT <= 1; xSHFT++)
				{
					if (xSHFT == 0 && ySHFT == 0)
						continue;
					int ni = i + ySHFT;
					if (ni == -1)
						ni += HEIGHT;
					int nj = j + xSHFT;
					if (nj == -1)
						nj += WIDTH;
					if (src[ni % HEIGHT][nj % WIDTH] == 1)
					{
						neighbours++;
					}
				}
			}
			if (src[i][j] == 1) 
			{
				if (neighbours < 2 || neighbours > 3) 
					dest[i][j] = 0;
				else 
					dest[i][j] = 1;
			}
			else if (src[i][j] == 0) 
			{
				if (neighbours == 3) 
					dest[i][j] = 1;
				else 
					dest[i][j] = 0;
			}
		}
	}

	//print_m(dest);
	clock_t end = clock();
	float seconds = (float)(end - start) / CLOCKS_PER_SEC;
	printf("%f", seconds);
	getchar();
}
