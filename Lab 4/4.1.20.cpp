#include <iostream>
#include <conio.h>
#include <cstring>
#include <windows.h>

using namespace std;

int main () 
{
	SetConsoleCP(1251);
  	SetConsoleOutputCP(1251);
	
	cout << "Эта программа проверяет текст на периодичность (период не превышает одного слова). Введите текст:\n";
	
	string text;
	getline (cin, text);
	
	//создание строки для сравнения
	string temp_str;
	int counter;
	for (counter = 0; text[counter] != ' '; counter++)
	{
		temp_str += text[counter];
	}
	temp_str += ' ';
	counter++;
	
	//проверка на периодичность
	bool period = true;
	for (int i = 0, j = 0; text[counter + j] != '\0'; i++, j++)
	{
		if (temp_str[i-1] == ' ')
			i = 0;
			
		if (temp_str[i] != text[counter + j])
		{
			period = false;
		}
	
	
		if (period == false)
		{
			cout << "Строка не периодична.\n";
			break;
		}
	}
	
	if (period == true)
		cout << "Строка периодична.\n";
	
	getch();
	return 0;
}
