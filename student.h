#pragma once
#include <string>
#include <map>

struct Unit
{
	std::string code;
	float mark;
};

struct Course
{
	std::string name, code;
	int aggregate{};
	std::map<std::string, float> units;
};

class Student
{
public:
	std::string name, regNum, gender;
	short age, year;
	Student *next;
	Course course;

	Student();
	// create
	void setupStudent();
	float setAggregate();
	void addUnit();
	// read
	void getStudentDetails(bool mode);
	// edit
	void editStudentProfile(std::string _name, std::string _regNum, std::string _gender, short _age);
	void editStudentAcademics(std::string _name, std::string _code);
	// delete
	//  void deleteStudent(); // moved to stack
	void deleteUnits();

	~Student();

private:
};