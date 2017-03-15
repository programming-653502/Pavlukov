#include <iostream>
#include <conio.h>
#include <cstring>
#include <windows.h>

using namespace std;

int main () 
{
	SetConsoleCP(1251);
  	SetConsoleOutputCP(1251);
	
	cout << "Ёта программа провер€ет текст на периодичность (период не превышает одного слова). ¬ведите свой текст:\n";
	
	string text;
	getline (cin, text);
	
	//создание строки дл€ сравнени€
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
			cout << "—трока не €вл€етс€ периодчиной.\n";
			break;
		}
	}
	
	if (period == true)
		cout << "—трока €вл€етс€ периодичной.\n";
	
	getch();
	return 0;
}
