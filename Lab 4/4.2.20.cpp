#include <stdio.h>
#include <windows.h>
#include <conio.h>

void AverageLen(FILE *file, char *buffer, int FSize)
{
	float word = 1, sentence = 0, letter = 0, averageSentenceLen, averageWordLen;
	
	while (fgets(buffer, FSize, file) != NULL)
		for (int i = 0; i < strlen(buffer); i++)
		{
			if (buffer[i] != ' ' & buffer[i] != '.' & buffer[i] != '!' & buffer[i] != '?' & buffer[i] != ',' & buffer[i] != ':' & buffer[i] != ';')
				letter++;
			if (buffer[i] == ' ')
				word++;
			if (buffer[i] == '.' || buffer[i] == '!' || buffer[i] == '?')
				sentence++;
		}
		
	averageWordLen = letter / word;
	averageSentenceLen = word / sentence;
	printf("Ñðåäíåå ÷èñëî áóêâ â ñëîâå: %f.\nÑðåäíåå ÷èñëî ñëîâ â ïðåäëîæåíèè: %f.\n", averageWordLen, averageSentenceLen);
}

void LongestWord(char *buffer, int FSize)
{
	int i, current = 0, max = 0, count = 0;
	
	for (i = 0; i < FSize; i++)
	{
		if (buffer[i] != ' ' & buffer[i] != '.' & buffer[i] != '!' &	buffer[i] != '?' & buffer[i] != ',' & buffer[i] != ':' & buffer[i] != ';')
			count++;
		else
		{
			if (count > max)
			{
				max = count;
				current = i - count;
			}
			count = 0;
		}
	}

	if (count > max)
	{
		max = count;
		current = i - count;
	}
	max += current;
	printf("Ñàìîå äëèííîå ñëîâî: ");
	for (i = current; i < max; i++)
		putchar(buffer[i]);
	printf("\n");
}

void LongestSentence(char *buffer, int FSize)
{
	int i, current = 0, max = 0, count = 0;
	
	for (i = 0; i < FSize; i++)
	{
		if (buffer[i] != '.' & buffer[i] != '!' & buffer[i] != '?' & buffer[i] != '\0')
			count++;
		else
		{
			if (count > max)
			{
				max = count;
				current = i - count;
			}
			count = 0;
		}
	}

	if (count > max)
	{
		max = count;
		current = i - count;
	}
	max += current;
	printf("Ñàìîå äëèííîå ïðåäëîæåíèå: ");
	for (i = current; i <= max; i++)
		putchar(buffer[i]);
	printf("\n");
}

int main()
{		
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	
	char *buffer, adress[100];
	long FSize;
	FILE *file;
	
	printf("Ââåäèòå èìÿ ôàéëà: \n");//ввод имени файла.
	gets(adress);
	file = fopen(adress, "r");
	
	if (file == NULL)
	{
		printf("Ôàéë íå íàéäåí.");
		getch();
		exit(1);
	}
	
	fseek(file, 0, SEEK_END);
	FSize = ftell(file) + 1;
	rewind(file);
	buffer = new char[FSize];
	
	if (buffer == NULL)
	{
		printf("Ôàéë ïóñò.");
		getch();
		exit(2);
	}
	if (!file) 
		exit(1);
	
	AverageLen(file, buffer, FSize);
	LongestWord(buffer, FSize);
	LongestSentence(buffer, FSize);

	fclose(file);
	free(buffer);
	getch();
	return 0;
}
