#include <iostream>
#include <conio.h>
#include <time.h>
#include <stdlib.h>

using namespace std;

int main ()
{
	srand(time(0));
	setlocale (0, "rus");
	
	int n;
	printf ("¬ведите размерность куба: ");
	scanf ("%i", &n);
	
	int ***cube = new int **[n];
	for (int i = 0; i < n; i++)
	{
		cube[i] = new int *[n];
		for (int j = 0; j < n; j++)
			cube[i][j] = new int [n];
	}
	
	//заполнение куба
	for (int z = 0; z < n; z++)
	{
		for (int y = 0; y < n; y++)
		{
			for (int x = 0; x < n; x++)
				cube[z][y][x] = rand() % 2;
		}
	}
	
	//вывод куба
	for (int z = 0; z < n; z++)
	{
		printf ("\n%i —лой:\n", z + 1);
		for (int y = 0; y < n; y++)
		{
			for (int x = 0; x < n; x++) 			
				printf ("\t%i", cube[z][y][x]);
				
			printf ("\n");
		}
		printf ("\n");
	}
	
	int counter = 0;
	//поиск просветов
	for (int z = 0; z < n; z++)
	{		
		for (int y = 0; y < n; y++)
		{
			int z_search = 0;
			int y_search = 0;
			int x_search = 0;
			for (int x = 0; x < n; x++)
			{
				x_search += cube[z][y][x];
				y_search += cube[z][x][y];
				z_search += cube[x][y][z];
			}
			
			if (x_search == 0)
			{
				counter++;
				printf ("\n\n%i просвет: слой: %i; строка: %i", counter, z + 1, y + 1);
			}
			
			if (y_search == 0)
			{
				counter++;
				printf ("\n\n%i просвет: слой: %i; столбец: %i", counter, z + 1, y + 1);
			}
			
			if (z_search == 0)
			{
				counter++;
				printf ("\n\n%i просвет: строка: %i; столбец: %i", counter, y + 1, z + 1);
			}
		}		
	}
	
	
	//удаление пам€ти
	for (int i = 0; i < n; i++) 
	{
        for (int j = 0; j < n; j++)
		{
            delete [] cube[i][j];
        }
        delete [] cube[i];
    }
    delete [] cube;
    
    
	getch();
	return 0;
}
