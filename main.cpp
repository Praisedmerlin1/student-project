#include <iostream>
#include "student.h"
#include "stack.h"

using namespace std;

int main()
{
	int option = 2;
	Student stud1;
	Stack stack;

	cout << "[1] run" << endl
		 << "[2] Read from file\n Or any other key to exit." << endl;
	cin >> option;

	switch (option)
	{
	case 1:
		stack.stackManager();
	case 2:
		stack.loadData();
		system("cls");
		stack.stackManager();

	default:
		cout << " exited ";
		break;
	}

	return 0;
}
