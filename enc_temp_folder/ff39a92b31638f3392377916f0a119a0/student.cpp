#include <iostream>
#include "student.h"
using namespace std;

Student::Student()
{
	name = "";
	regNum = "";
	age = 0;
	year = 0;
	gender = '\0';
	next = NULL;
}
Student::~Student()
{
}

// __________ CREATE _________________

// Add a unit
void Student::addUnit()
{
	bool option{false};

	do
	{
		Unit *unit = new Unit;
		option = 0;
		cout << "Do you want to add/edit a unit? yes(1), no(0)" << endl;
		cin >> option;

		if (option)
		{
			cout << "Enter the code of the unit and the marks in that unit as a percentage..." << endl;

			cout << "Code: ";
			cin >> unit->code;
			cout << "Marks: ";
			cin >> unit->mark;

			course.units[unit->code] = unit->mark;
			delete unit;

			cout << "Done! " << endl;
		}
		else
		{
			delete unit;
			break;
		}

	} while (option);
	return;
}

// Calculate the aggregate
float Student::setAggregate()
{
	short *counter = new short(0);
	float *temp = new float(0.0);

	cout << "Calculating aggregate..." << endl;

	for (auto &unit : course.units)
	{
		*counter += 1;
		*temp += unit.second;
	}

	course.aggregate = *temp / *counter;

	delete counter;
	delete temp;

	return course.aggregate;
}

// Setup the student for the first time
void Student::setupStudent()
{
	cout << "Enter the student's registration number, name, age and gender [M/F] "
		 << endl;
	cout << "Registration Number: ";
	cin >> regNum;
	cout << "Name: ";
	cin >> name;
	cout << "age: ";
	cin >> age;
	cout << "Gender [M/F]: ";
	cin >> gender;

	cout << "Done!" << endl
		 << "Enter the Course code, the course name, and the year of the student"
		 << endl;
	cout << "Course code: ";
	cin >> course.code;
	cout << "Course name: ";
	cin >> course.name;
	cout << "Year: ";
	cin >> year;
	cout << "Done!" << endl;
	addUnit();
	setAggregate();
}

//___________ READ __________________
// Since the variables are public ... they can be accessed directly

void Student::getStudentDetails(bool full)
{
	if (full)
	{
		// Full Student info
		cout << "Registration Number:\t" << regNum
			 << "\nName:\t" << name
			 << "\nage: " << age << "\tGender: " << gender
			 << "\tCourse:\t" << course.name;
		cout << "Units \n";

		for (auto unit : course.units)
		{
			cout << unit.first << "\t" << unit.second << endl;
		}

		cout << "Aggregate: " << course.aggregate << endl;
		return;
	}
	else
	{
		// Basic Student info
		cout << "Registration Number:\t" << regNum
			 << endl
			 << "Name:\t" << name
			 << endl
			 << "Course:\t" << course.name;
	}
}

//__________ EDIT __________________

void Student::editStudentProfile(string _name, string _regNum, string _gender, short _age)
{
	// if the value is the same or unchanged keep the old value
	name = (_name == "/n" || _name == name) ? name : _name;
	regNum = (_regNum == "/n" || _regNum == regNum) ? regNum : _regNum;
	gender = (_gender == "/n" || _gender == gender) ? gender : _gender;
	age = (_age <= 0 || _age == age) ? age : _age;
}
void Student::editStudentAcademics(string _name, string _code)
{
	bool option = false;
	course.name = (_name == "/n" || _name == course.name) ? course.name : _name;
	course.code = (_code == "/n" || _code == course.name) ? course.code : _code;

	cout << "Do you want to edit[0] or delete[1] ";
	cin >> option;
	if (option)
	{
		cout << "Are you sure you want to delete ALL units? Yes[1] , NO[0]" << endl;
		cin >> option;
		if (option)
		{
			deleteUnits();
			cout << "Units deleted..";
			return;
		}
		return;
	}
	else
	{
		addUnit();
	}
}

//__________ DELETE ________________
void Student::deleteUnits()
{
	course.units.clear();
}