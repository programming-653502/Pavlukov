#include <iostream>
#include <conio.h>
#include <windows.h>
#include <math.h>

using namespace std;
  
int main() 
{
	SetConsoleCP(1251);
  	SetConsoleOutputCP(1251);
	
	unsigned int divider, dividend, division;
		
	printf ("Введите делимое и делитель: ");
	scanf ("%i %i", &dividend, &divider);
		
	division = dividend / divider;
	printf ("\n %i\t| %i\n\t________\n-\t| %i\n", dividend, divider, division);
		
	int i, temp_div = dividend;	
    for (i = 1; dividend / pow(10, i) >= divider; i++)
    {
    	temp_div /= 10;
	}
	
	int temp_dividend;
	for (int num = 0; num <= 9 && divider * num <= temp_div; num++)
	{
		temp_dividend = divider * num;
	}
	temp_div -= temp_dividend;
	printf (" %i\n________\n %i\n", temp_dividend, temp_div);
	
	for (i -= 2; i >= 0; i--)
	{
		int temp = dividend / pow (10, i);
		temp_div = temp_div * 10 + temp % 10;
		printf ("\n %i\n-\n", temp_div);
		
		for (int num = 0; num <= 9 && divider * num <= temp_div; num++)
		{
			temp_dividend = divider * num;
		}
		temp_div -= temp_dividend;
		printf (" %i\n________\n %i\n", temp_dividend, temp_div);
		
	}
		
    getch();
    return 0;
}




