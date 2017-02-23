#include <conio.h>

using namespace std;

struct time
{
	int hour;
	int minute;	
};

//���� � ����� ������� ������.
void time_input (time *a, time *b)
{
	printf ("\n������� ����� ������ ������: ");
	cin >> a->hour >> a->minute;
	printf ("\n������� ����� ��������� ������: ");
	cin >> b->hour >> b->minute;	
	
	if (a->hour > 23 || a->hour < 0 || a->minute > 59 || a->minute < 0)
	{
		printf ("\a\n������� ���������� �����.");
		time_input(a, b);
	}
	
	if (b->hour > 23 || b->hour < 0 || b->minute > 59 || b->minute < 0)
	{
		printf ("\a\n������� ���������� �����.");
		time_input(a, b);
	}
	
	printf ("\n����� ������ ��������: %02i:%02i - %02i:%02i\n", a->hour, a->minute, b->hour, b->minute);
}

//������� � ����� ��������������� ���������� �����������
int num_of_people (int start_hour, int finish_hour)
{
	if (start_hour == -1)
	{
		printf ("\a\n��� ������ ������� ����� ������.\n");
			return 0;	
	}

	int num_ppl = 0;
	
	for (int i = start_hour; i <= finish_hour; i++)
	{
		int people = 0;
		if (i >= 9 && i < 13)
			people = 5;
		else if (i >= 13 && i < 18)
			people = 14;
		else if (i >= 18 && i < 23)
			people = 42;
			
		num_ppl += people;
	}
	
	printf ("\n�������������� ���������� ����������� � ���� ������ �� %02i �� %02i ���������� %i �������.\n", start_hour, finish_hour, num_ppl);
	
	return num_ppl;
}

//������� ������������ � ����� ��������� / �����-���� 
int price (int ppl)
{
	
	float ham = 0, mushroom = 0, vegetable = 0, flour = 0, price = 0, price_of_one = 0;
	
	printf ("\n�������� �����:\n1 - � �������� � �������.\n2 - � �������� � �������.\n3 - � ��������, ������� � �������.\n");
	char choice = getch();
	switch (choice) 
	{
		case '1': 
		{
			mushroom = 0.08 * ppl;
			vegetable = 0;
			break;
		}
		
		case '2': 
		{
			mushroom = 0;
			vegetable = 0.15 * ppl;
			break;
		}
			
		case '3':
		{
			mushroom = 0.08 * ppl;
			vegetable = 0.15 * ppl;
			break;
		}
		
		default: 
		{
			printf ("\a\n������������ �����.\n");
			return 0;
		}
	}
	ham = 0.09 * ppl;
	flour = 0.15 * ppl;
	price = ham * 7000 + mushroom * 10000 + vegetable * 3000 + flour * 1500;
	price_of_one = 4.5 * price;
	
	if (ppl != 1)
	{	
		printf ("\n����������� ���������� ������������ �� %i ����:\n�������: %.3f ��.\n�����: %.3f ��.\n�����: %.3f ��.\n����: %.3f ��.", ppl, ham, mushroom, vegetable, flour);
		printf ("\n--------------------------------------------------------------------\n");
		printf ("����� ��������� ���������: %.2f ���.\n", price);
	}
	else 
	{	
		printf ("���� �� 1 ��.: %.2f ���.", price_of_one);
	}
	
	return price_of_one;
}

void profit_calc (float price_of_one, int ppl)
{
	float profit = price_of_one * ppl * 0.1;
	printf ("\n�������������� ������� �� ��������� ���������� �������: %f\n", profit);
}


int main()
{
	setlocale (0, "rus");
	
	time start_time, finish_time;
	start_time.hour = -1;
	time *p = &start_time;
	time *p1 = &finish_time;
	int num_of_ppl = 0;
	int price_of_one = 0;
	
	for (;;)
	{
		printf ("\n\t\t\tMENU\n");
		printf ("\n--------------------------------------------------------------------\n");
		printf ("\n1 - ���� ���������� ������� ������ ��������.\n2 - ����� ��������������� ���������� �����������.\n3 - ������ ���������� ������������ � ����� ����� ��������� ������.");
		printf ("\n4 - �������������� ������(��������� �����).\n5 - ������ �������������� ������� �� ��������� ���������� �������.\n6 - ���������� � ������ � ������ ���������.\n0 - �����.\n");
		printf ("\n--------------------------------------------------------------------\n");
		
		char choice = getch();
		switch (choice)
		{
			case '1':
				{
					time_input (p, p1);
					break;
				}
				
			case '2':
				{
					num_of_ppl = num_of_people (start_time.hour, finish_time.hour);
					break;
				}
				
			case '3':
				{
					price (num_of_ppl);
					break;
				}
				
			case '4':
				{
					price_of_one = price (1);
					break;
				}
				
			case '5':
				{
					profit_calc (price_of_one, num_of_ppl);
					break;
				}
				
			case '6':
				{
					printf ("\nv. 1.1\nCreated by Sergey Pavlukov.\n");
					break;
				}
				
			case '0':
				{
					break;
				}
				
			default: 
				{
					printf("\a\n������������ �����.\n");
					break;
				}
		}
		


		//����� �� ���������
		if (choice == '0')
			break;
			
		getch();
	}

	return 0;
}
