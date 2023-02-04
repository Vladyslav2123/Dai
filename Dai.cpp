#include <iostream>
#include <iomanip>
#include <conio.h>
#include <fstream>
#include "List.h"
#include "Tree.h"

using namespace std;

class Protocol {
private:
	char* _car_number;
	char* _offense;
public:
	Protocol(const char* number = nullptr, const char* off = nullptr);
	Protocol(const Protocol& other);
	~Protocol()
	{
		clear();
	}

	void setNumber(const char* number);
	void setOffense(const char* off);

	char* getNumber()const { return _car_number; }
	char* getOffense()const { return _offense; }

	void clear();

	friend ostream& operator<<(ostream& out, const Protocol& ptr);
	friend ostream& operator<<(ostream& out, const Protocol* ptr);
	friend istream& operator>>(istream& in, Protocol& ptr);
	friend istream& operator>>(istream& in, Protocol* ptr);
};

class BaseMenu
{
	BTree<string, FList<Protocol*>> base;

public:
	void menu();
	void addProtocol();
	void print();
	void printNum();
	void printRange();
};

void BaseMenu::menu()
{
	do
	{
		system("cls");
		cout << "1. Add Protocol" << endl;
		cout << "2. Print all" << endl;
		cout << "3. Search by vehicle number" << endl;
		cout << "4. Print across a range of numbers" << endl;
		cout << "0. Exit" << endl;
		int n;
		cin >> n;
		cin.ignore();
		switch (n)
		{
		case 1:
			system("cls");
			addProtocol();
			break;
		case 2:
			system("cls");
			print();
			break;
		case 3:
			system("cls");
			printNum();
			break;
		case 4:
			system("cls");
			printRange();
			break;
		case 0:
		{
			base.clear();
			exit(0);
		}
		default:
			break;
		}
	} while (true);
}

inline void BaseMenu::addProtocol()
{
	cout << " Add Protocol: " << endl;
	cout << "-------------------" << endl;
	Protocol* prot = new Protocol;
	cin >> prot;
	FList<Protocol*>* list = base.get(prot->getNumber());
	if (!list)
	{
		cout << "This vehicle number is not in the database and will be added" << endl;
		FList<Protocol*> newList;
		newList.push_front(prot);
		base.push_r(prot->getNumber(), newList);
	}
	else
	{
		list->push_back(prot);
	}
	cout << "New protocol added" << endl;
}

inline void BaseMenu::print()
{
	cout << left << setw(25) << "Vehicle number" << right << "Protocol" << endl;
	cout << "______________________________________________________________________________\n";
	base.print();
	system("pause");
}

inline void BaseMenu::printNum()
{
	cout << "Search for the protocol by vehicle number:" << endl;
	cout << "-----------------------------" << endl;
	char num[100];
	cout << "Vehicle number: ";
	cin >> num;
	FList<Protocol*>* list = base.get(num);
	system("cls");
	if (list)
	{
		cout << left << setw(25) << "Vehicle number" << right << "Protocol" << endl;
		cout << "______________________________________________________________________________\n";
		list->print();
	}
	else
		cout << "Protocol by vehicle number " << num << " not found" << endl;
	system("pause");
}

inline void BaseMenu::printRange()
{
	cout << " Search for protocols by the range of vehicle numbers:" << endl;
	cout << "-----------------------------------------" << endl;
	char num[10], num2[10];
	cout << "First vehicle number: ";
	cin >> num;
	cout << "Second vehicle number:  ";
	cin >> num2;

	FList<Protocol*>* list = base.get(num);
	FList<Protocol*>* list2 = base.get(num2);
	system("cls");
	if (list)
		cout << "Number " << num << " found in database" << endl;
	else
		cout << "Number " << num << " not found in database" << endl;
	if (list2)
		cout << "Number " << num2 << " found in database" << endl;
	else
		cout << "Number " << num2 << " not found in database" << endl;

	if (num < num2)
		swap(num, num2);

	if (list && list2)
	{
		cout << left << setw(25) << "Vehicle number" << right << "Protocol" << endl;
		cout << "______________________________________________________________________________\n";
		base.printD(num, num2);
	}
	else
		cout << "Enter correctly the range of numbers to search!" << endl;
	system("pause");
}

Protocol::Protocol(const char* number, const char* off)
{
	_car_number = _strdup(number);
	_offense = _strdup(off);
}

Protocol::Protocol(const Protocol& other)
{
	if (&other == this) return;

	if (_car_number) delete[]_car_number;
	_car_number = _strdup(other._car_number);

	if (_offense) delete[]_offense;
	_offense = _strdup(other._offense);
}

void Protocol::setNumber(const char* number)
{
	if (_car_number) delete[]_car_number;
	_car_number = _strdup(number);
}

void Protocol::setOffense(const char* off)
{
	if (_offense) delete[]_offense;
	_offense = _strdup(off);
}

void Protocol::clear()
{
	delete[] _car_number;
	delete[] _offense;
}

ostream& operator<<(ostream& out, const Protocol& ptr)
{
	out << left << setw(25) << (ptr._car_number ? ptr._car_number : "No number!") << right << (ptr._offense ? ptr._offense : "No offense!") << endl;
	return out;
}

ostream& operator<<(ostream& out, const Protocol* ptr)
{
	out << left << setw(25) << (ptr->_car_number ? ptr->_car_number : "No number!") << right << (ptr->_offense ? ptr->_offense : "No offense!") << endl;
	return out;
}

istream& operator >> (istream& in, Protocol& ptr)
{
	ptr._car_number = new char[50];
	ptr._offense = new char[1000];
	cout << "Enter number: " << endl;
	in.getline(ptr._car_number, 50);
	cout << "Enter offense: " << endl;
	in.getline(ptr._offense, 1000);
	in.ignore();
	return in;
}

istream& operator>>(istream& in, Protocol* ptr)
{
	ptr->_car_number = new char[50];
	ptr->_offense = new char[100];
	cout << "Enter number: " << endl;
	in.getline(ptr->_car_number, 50);
	cout << "Enter offense: " << endl;
	in.getline(ptr->_offense, 50);
	in.ignore();
	return in;
}

int main()
{
	BaseMenu menu;
	menu.menu();

	return 0;
}