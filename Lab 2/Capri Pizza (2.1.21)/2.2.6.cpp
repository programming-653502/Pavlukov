#include <iostream>
#include <conio.h>
#include <math.h>

using namespace std;

double fact (int n)
{
	double fact = 1;
	
	for (int i = 1; i <= n; i++)
	{
		fact *= i;
	}
	
	return fact;	
}

int main () 
{
	setlocale (0, "rus");
	
	double x, result_sin, result_func = 0, n;
	
	cout << "Введите число n, от которого нужно посчитать функцию: ";
	cin >> n;
	cout << "Введите число x: ";
	cin >> x;
	
	result_sin = sin (x);
	
	for (int i = 1; i <= n; i++)
	{
		result_func += pow (-1, i - 1) * pow (x, 2 * i - 1) / fact (2 * i - 1);
	}
	
	printf ("%f = %f\n", result_sin, result_func);
	
	getch();
	return 0;
}
