#include <conio.h>
#include <iostream>
#include <windows.h>

using namespace std;
int odd_count = 0;

struct Tree 
{
	Tree *left;
	Tree *right;
	int value;
};

void Add(int x, Tree *&Node)
{
	if (Node == NULL)
	{
		Node = new Tree;
		Node->value = x;
		Node->left = Node->right = NULL;
	}
	
	if(x < Node->value)
	{
		if(Node->left != NULL)
			Add(x, Node->left);
		else 
		{
			Node->left = new Tree;
			Node->left->left = Node->left->right = NULL;
			Node->left->value = x;
		}
	}
	else if(x > Node->value)
	{
		if(Node->right != NULL)
			Add(x, Node->right);
		else
		{
			Node->right = new Tree;
			Node->right->left = Node->right->right = NULL;
			Node->right->value = x;
		}		
	}
}

void ShowOdd(Tree *&Node)
{
	if(Node == NULL)
		return;
		
	ShowOdd(Node->left);
	if(Node->value % 2 != 0)
		odd_count++;
	ShowOdd(Node->right);	
}
	
int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	
	Tree *SearchTree = NULL;
	FILE *f;
	f = fopen("File.txt", "r");
	if (f == NULL) 
	{
		cout << "\aÔàéë íå íàéäåí.";
		getch();
		return 1;
	}
	else 
	{
		while (!feof(f)) 
		{
			int temp;
			fscanf(f, "%d ", &temp);
			Add(temp, SearchTree);
			cout << temp << " ";
		}
	}

	cout << "\n";
	ShowOdd(SearchTree);
	cout << "Êîëè÷åñòâî íå÷åòíûõ ÷èñåë: " << odd_count; 
	
	getch();
	return 0;
}
