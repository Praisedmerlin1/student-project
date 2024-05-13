#pragma once

#include <vector>
#include "student.h"

class Stack
{
public:
	Student* first;
	std::vector<Student*> students;
	bool sorted = false;
	

	Stack();
	bool isEmpty();
	bool checkIfRegExist(Student* s);
	bool checkIfRegExist(std::string s);
	void sort(bool mode);
	int readFile(std::vector<Student*> &student);
	void push(Student* s);
	Student* pop();
	Student* peek();
	int count();
	Student* search(std::string regNum);
	void display();
	void loadData();
	void stackManager();
	//read student
	void studentDetails(std::string regNum);
	//edit student
	void editStudent(std::string regNum);
	//delete student
	void deleteStudent(std::string regNum);

private:

};
