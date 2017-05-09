#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#include <conio.h>
#include <iomanip>
#include <windows.h>

using namespace std;

class User
{
public:
    int sum;
    string name, password;
    User()
    {
        sum = 0;
        name = password = "";
    }
};

void error(int param)
{
    switch(param)
    {
        case 1:
            cerr << "\a\nОшибка. Список пуст." << endl;
            exit(1);
    }
}

struct Node
{
    User user;
    Node* next;
    Node* prev;
};

class List
{
public:
    List();
    void push_back(User);
    void push_front(User);
    User pop_back();
    User pop_front();
    bool is_empty();
    bool search(User&);
    void print();
    void remove(User&);
    bool changesum(User&, int);
    ~List();
    Node* head;
};

void List::remove(User& user)
{
    Node* cur = head;
    while(cur)
    {
        if(user.name == cur->user.name)
        {
            break;
        }
        cur = cur->next;
    }
    
    if(!head)
		return;
		
    if(cur->next != 0) 
        cur->next->prev = cur->prev;
 
    if(cur->prev != 0)
        cur->prev->next = cur->next;
}

bool List::search(User& user)
{
    bool res = false;
    Node* cur = head;
    while(cur)
    {
        if(user.name == cur->user.name)
        {
            res = true;
            user.password = cur->user.password;
            user.sum = cur->user.sum;
            break;
        }
        cur = cur->next;
    }
    return res;
}

bool List::changesum(User&user, int sum)
{
    bool res = true;
    Node*cur = head;
    while(cur)
    {
        if(user.name == cur->user.name)
        {
            if(cur->user.sum + sum < 0)
            {
                cout << "\nНевозможно изменить сумму счета.\n";
                res = false;
                break;
            }
            else
                cur->user.sum += sum;            
        }
        cur = cur->next;
    }
    return res;
}

void List::print()
{
    if(is_empty())
        cout << "\nСписок аккаунтов пуст.\n" << endl;
    else
    {
        Node* cur = head;
        while(cur)
        {
            cout << setw(15) << cur->user.name << " |" << setw(20) << cur->user.password << " |" << setw(14) << cur->user.sum << " |\n";
            cur = cur->next;
        }
    }
}

List::List()
{
    head = 0;
}

List::~List()
{
    if(!is_empty())
    {
        while(head->next)
        {
            head = head->next;
            delete head->prev;
        }
        delete head;
    }
}

bool List::is_empty()
{
    return !head;
}

void List::push_back(User usr)
{
    if(is_empty())
    {
        Node* tmp = new Node;
        tmp->user = usr;
        tmp->prev = 0;
        tmp->next = 0;
        head = tmp;
    }
    else
    {
        Node* cur = head;
        while(cur->next)
        	cur = cur->next;
        	
        Node* tmp = new Node;
        tmp->user = usr;
        tmp->prev = cur;
        tmp->next = 0;
        cur->next = tmp;
    }
}

User List::pop_back()
{
    if(is_empty())
        error(1);
    else
    {
        Node* cur = head;
        while(cur->next)
            cur = cur->next;
            
        User temp = cur->user;
        if(!(cur->prev))
            head = 0;
        else
            cur->prev->next = 0;
            
        delete cur;
        return temp;
    }
}

void List::push_front(User usr)
{
    if(is_empty())
        push_back(usr);
    else
    {
        Node* tmp = new Node;
        tmp->user = usr;
        tmp->next = head;
        tmp->prev = 0;
        head->prev = tmp;
        head = tmp;
    }
}

User List::pop_front()
{
    if(is_empty())
        error(1);
    else
    {
        User temp = head->user;
        Node* tmp = head;
        head = tmp->next;
        if(head)
            head->prev = 0;
            
        delete tmp;
        return temp;
    }
}

int convertToInt(string s)
{
    int res = 0;
    for (int i = s.size() - 1; i >= 0 ; i--)
        res += (int)((int)(s[i] - 48) * pow(10, s.size() - 1 - i));
        
    return res;
}

vector<string> parseString(string s)
{
    vector<string> res;
    int i = 0;
    int j = 0;
    while(i != s.size())
    {
        if(s[i] == ' ' && s[j] != ' ')
		{
            res.push_back(s.substr(j, i - j));
            j = i + 1;
        }
        i++;
        if(i == s.size() - 1 && s[i] != ' ' && s[j] != ' ')
            res.push_back(s.substr(j, i - j + 1));
    }
    
    return res;
}

void printmenue()
{
    cout << "1 - Посмотреть сумму счета\n";
    cout << "2 - Перевести деньги другому пользователю\n";
    cout << "3 - Удалить свой аккаунт\n";
    cout << "0 - Выйти\n";
}

fstream inputFile, outputFile;

bool signin(List &list, User&user)
{
	cout << setw(49) << "СПИСОК ПОЛЬЗОВАТЕЛЕЙ\n";
	cout << setw(17) << "ИМЯ |" << setw(22) << "ПАРОЛЬ |"<< setw(17) << "СУММА СЧЕТА |\n";
	list.print();
	
    cout << "\n" << setw(53) << "АВТОРИЗАЦИЯ\nВведите имя:";
    cin >> user.name;
    cout << "\nВведите пароль:";
    string password;
    cin >> password;

    if(!list.search(user))
        return false;

    if(user.password != password)
        return false;

    cout << "Авторизация прошла успешно! Нажмите любую клавишу, чтобы продолжить!\n";
	getch();
	system("cls");
    return true;
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	
	List users;
	
    inputFile.open("UserList.txt",ios::in);
    string str;
    while(getline(inputFile,str))
    {
        User user;
        user.name = parseString(str)[0];
        user.password = parseString(str)[1];
        user.sum = convertToInt(parseString(str)[2]);
        users.push_back(user);
    }
    inputFile.close();
    
    cout << setw(49) << "СПИСОК ПОЛЬЗОВАТЕЛЕЙ\n";
	cout << setw(17) << "ИМЯ |" << setw(22) << "ПАРОЛЬ |"<< setw(17) << "СУММА СЧЕТА |\n";
    users.print();	
		
	getch();
	system("cls");
		
	User current_user;
	
    bool start = true;
	
	while(start)
	{
	    bool run = false, exit = false;
	    
	    char choice;
		cout << "\n1 - Войти.\n2 - Зарегистрироваться.\n";
		cin >> choice;
		if (choice == '1')
		{
			system("cls");
			
			if(signin(users, current_user))
				run = true;
			else
				cout << "\n\aОшибка. Неверный логин или пароль.\n";
		}
		else if(choice == '2')
		{
			system("cls");
			
		    User user;
			cout << "Введите имя пользователя:\n";
			cin >> user.name;
			cout << "Введите пароль:\n";
			cin >> user.password;
			user.sum = 1000;
		                
			inputFile.open("UserList.txt",ios::app);
			inputFile << user.name << " " << user.password << " " << user.sum << "\n";
			inputFile.close();	
			
			outputFile.open("ActionList.txt", ios::app);
			outputFile << "Новый пользователь добавлен: " << user.name << ". Его сумма счета: " << user.sum << "$\n";
			outputFile.close(); 
		
			users.push_back(user);
			getch();				
		}
		else
			cout << "\n\aОшибка. Повторите ввод.\n";
	
		while(run)
	    {
	        char a;
	        printmenue();
	        cin >> a;
	        switch(a)
	        {
	        	case '1':
		        	{
		            	system("cls");
			    		cout << "Ваша сумма счета: " << current_user.sum;
			            getch();
						system("cls");
	            		break;
					}
						
				case '2':
					{
						system("cls");
		                User user1;
		                cout << setw(49) << "СПИСОК ПОЛЬЗОВАТЕЛЕЙ\n";
					    cout << setw(17) << "ИМЯ |" << setw(22) << "ПАРОЛЬ |"<< setw(17) << "СУММА СЧЕТА |\n";
					    users.print();
					    
		                cout << "Имя пользователя, которому вы хотите перевести деньги:\n";
		                while(true)
		                {
			                try
							{
			                	cin >> user1.name;
			                }
							catch(exception e)
							{
			                	cout << "\a\nОшибка ввода! Попробуйте заново!\n";
			                	continue;
							}
							break;
						}
							
			            cout << "--------------------\n";
			                
		                if (!users.search(user1)) 
						{
			                cout << "\n\aОшибка ввода.\n";
			                getch();
		                    system("cls");
		                }
		                else
		                {
			                cout << "Сумма вашего счета: " << current_user.sum << "$. Введите сумму перевода:\n";
			                int sum = 0;
			                while(true)
			                {
				                try
								{
				                	cin >> sum;
				                }
								catch(exception e)
								{
				                	cout<<"\n\aОшибка ввода! Попробуйте завново!\n";
				                	continue;
								}
								break;
							}
								
			                if (sum < 0) 
							{
			                    cout << "\n\aОшибка. Неверная сумма.";
			                    getch();
			                    system("cls");
			                }
			                else
			                {
				                if (sum > current_user.sum) 
								{
				                    cout << "\n\aОшибка. У вас недостаточно средств.\n";
				                    getch();
				                    system("cls");
				                }
				                else
				                {
					                outputFile.open("ActionList.txt", ios::app);						
					                outputFile << "Перевод денег от " << current_user.name <<  " к " << user1.name << ". Сумма перевода: " << sum << "\n";									
									outputFile.close();
										
					                try
						            {							                
						                users.changesum(current_user, -sum);
						                users.changesum(user1, sum);
						                inputFile.open("UserList.txt",ios::out);
						                Node*cur = users.head;
						                while(cur)
										{
						                	inputFile << cur->user.name << " " << cur->user.password << " " << cur->user.sum << "\n";
						                	cur = cur->next;
										}
						                inputFile.close();
						                
						                cout<<"Операция прошла успешно!\n(нажмите Enter, чтобы продолжить)\n";
					            	}
									catch(exception e)
					            	{
					            		cout<<"\n\aОшибка. Операция не завершена.\n(нажмите любую клавишу, чтобы продолжить)\n";
									}
					                getch();
									system("cls");
								}
							}
						}
						break;
					}
						
				case '3':
					{
						system("cls");
						
						char a;
			            cout << "\n\aВы уверены, что хотите безвозвратно удалить свой аккаунт? Введите Y, чтобы продолжить\n";
			            cin >> a;
			            if(a == 'Y')
			            {   
				            users.remove(current_user);
					        outputFile.open("ActionList.txt", ios::app);
					        outputFile << "Удаление пользователя: " << current_user.name << "\n";
					        outputFile.close();
					                
					        inputFile.open("UserList.txt",ios::out);
						    Node* cur = users.head;
							while(cur)
							{
							    inputFile << cur->user.name << " " << cur->user.password << " " << cur->user.sum << "\n";
							    cur = cur->next;
							}
							inputFile.close();
								        
					        cout << "Удаление прошло успешно.\n";
					        getch();
							return 0;	
						}
						
						break;		
					}
						
				case '0':
					{
						return 0;
						break;	
					}
						
				default:
					{
						cout << "\n\aОшибка. Повторите ввод\n";
		                getch();
						system("cls");
						break;
					}				
			}
        }
	}
    return 0;
}
