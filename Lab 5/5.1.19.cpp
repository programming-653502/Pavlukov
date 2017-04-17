#include <iostream>
#include <conio.h>
#include <windows.h>
#include <math.h>
#include <algorithm>// для reverse

using namespace std;

unsigned int CheckForInt()
{
	unsigned int num;
	bool check = false;
	while(check == false)
	{
		cin >> num ;
		if(cin.good())
		{
			check = true;
		}
		else
		{		
			printf("Îøèáêà ââîäà.\nÂâåäèòå ÷èñëî â äåñÿòè÷íîé ñèñòåìå: ");
			cin.clear();
			_flushall();
		}
	}
	return num;
}

string ConvertToBin(unsigned int number)
{
	string bin_num = "";
	while(true)
	{
		if ( number == 0 )
		{
			 bin_num += "0";
			 break;
		}
	    if ( number == 1 ) 
	    {
			bin_num += "1";
			break;
		}
		
	    if ( number % 2 == 0 )
	        bin_num += "0";
	    else
	        bin_num += "1";
	        
	    number /= 2;
	}
	reverse(bin_num.begin(), bin_num.end());
	return bin_num;
}

struct DecNum
{
	unsigned int num;
	DecNum *Next;
	DecNum *Prev;	
};

class List
{
	DecNum *Head = NULL, *Tail = NULL;
	string bin_num = "";
	int degree = -1;//степень десяти
	
	public:
		void Add(unsigned int num);
		void Show();
		void ToBin();
		
};

void List::Add(unsigned int num)
{
	DecNum *tmp = new DecNum;
	tmp->Next = NULL;
	tmp->num = num;
	
	if(Head != NULL)
	{
		tmp->Prev = Tail;
		Tail->Next = tmp;
		Tail = tmp;
	}
	else
	{
		tmp->Prev = NULL;
		Head = Tail = tmp;
	}
}

void List::Show()
{
	DecNum *tmp = Tail;
	int counter = 1;
	
	while (tmp != NULL)
	{
		cout << counter << " öèôðà: " << tmp->num;
		tmp = tmp->Prev;
		cout << endl;
		degree++;
		counter++;
	}
	cout << endl;
}

void List::ToBin()
{
	DecNum *tmp = Tail;
	
	cout << "Ïåðåâîä â äâîè÷íóþ ñèñòåìó:\n";
	while (tmp != NULL)
	{
		unsigned int n = pow(10, degree) * tmp->num;
		bin_num = ConvertToBin(n);		
		cout << "\n  " << bin_num;
		if(tmp->Prev != NULL)
			cout << "\n+";
		else
			cout << "\n-----------------------\n  "; 
		
		degree--;
		tmp = tmp->Prev;		
	}		
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	
	List dec;
	unsigned int num_dec, tmp;
	
	cout << "Ââåäèòå ÷èñëî â äåñÿòè÷íîé ñèñòåìå: ";
	num_dec = CheckForInt();	
	tmp = num_dec;
	
	while (num_dec > 0)
	{
		dec.Add(num_dec % 10);
		num_dec /= 10;
	}
	
	dec.Show();
	dec.ToBin();
	
	cout << ConvertToBin(tmp);
	getch();
	return 0;
}
