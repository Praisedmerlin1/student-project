#include <iostream>
#include <fstream>
#include <sstream>

#include "student.h"
#include "stack.h"

using namespace std;
// Default constructor
Stack::Stack()
{
    first = NULL;
}

// Check if the stack is empty
bool Stack::isEmpty()
{
    if (first == NULL)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// Check if there is already a student with the key or regnum
bool Stack::checkIfRegExist(Student *s)
{
    Student *temp = first;
    bool exist = false;
    while (temp != NULL)
    {
        if (temp->regNum == s->regNum)
        {
            exist = true;
            break;
        }
        temp = temp->next;
    }
    return exist;
}
bool Stack::checkIfRegExist(string s)
{
    Student *temp = first;
    bool exist = false;
    while (temp != NULL)
    {
        if (temp->regNum == s)
        {
            exist = true;
            break;
        }
        temp = temp->next;
    }
    return exist;
}

// Sort the stack in a desired order
void Stack::sort(bool sortReg)
{
    // Get the number of students in the stack
    int num = count();
    Student *temp = NULL;

    if (sortReg)
    {
        for (int i = 0; i < num; i++)
        {
            for (int j = i + 1; j < num; j++)
            {
                if (students[i]->regNum > students[j]->regNum)
                {
                    temp = students[i];
                    students[i] = students[j];
                    students[j] = temp;
                }
            }
        }
        sorted = true;
    }
    else if (!sortReg)
    {
        for (int i = 0; i < num; i++)
        {
            for (int j = i + 1; j < num; j++)
            {
                if (students[i]->course.aggregate < students[j]->course.aggregate)
                {
                    temp = students[i];
                    students[i] = students[j];
                    students[j] = temp;
                }
            }
        }
        sorted = false;
    }

    first = students[0];
    first->next = students[1];

    for (int k = 1; k < num - 1; k++)
    {
        students[k]->next = students[k + 1];
    }

    students[num - 1]->next = NULL;
}

// push students into the stack
void Stack::push(Student *s)
{
    // first generate a key from the registration number

    if (first == NULL)
    {
        first = s;
        cout << "Node PUSHED successfully" << endl;
    }
    else if (checkIfRegExist(s))
    {
        cout << "Node already exist with this Key value."
             << "Enter different Key value" << endl;
    }
    else
    {
        Student *temp = first;
        first = s;
        s->next = temp;
        cout << "Node PUSHED successfully" << endl;
        sorted = false;
    }
}

// Pop the first student from the sorted stack
Student *Stack::pop()
{
    Student *temp = NULL;

    if (isEmpty())
    {
        cout << "stack underflow" << endl;
        return temp;
    }
    else
    {
        temp = first;
        first = first->next;
        return temp;
    }
}

// Get the first student
Student *Stack::peek()
{
    // Student *temp = NULL;
    if (isEmpty())
    {
        cout << "stack underflow" << endl;
        return NULL;
    }
    else
    {
        return first;
    }
}

// Get the number of students in the stack
// and save their pointers for later use
int Stack::count()
{
    // If the vector has items remove it
    students.clear();
    int count = 0;

    Student *temp = first;
    while (temp != NULL)
    {
        students.emplace_back(temp);
        count++;
        temp = temp->next;
    }
    return count;
}

// search for a student using a registration number
Student *Stack::search(string regNum)
{
    int num = count();
    if (!sorted)
    {
        sort(true);
    }

    int left = 0;
    int right = num;
    while (left <= right)
    {
        int mid = left + (right - left) / 2;
        if (students[mid]->regNum == regNum)
        {
            return students[mid];
        }
        else if (students[mid]->regNum < regNum)
        {
            left = mid + 1;
        }
        else
        {
            right = mid - 1;
        }
    }
    return NULL;
}

// Show all the students in the stack
void Stack::display()
{

    cout << "All values in the Stack are :" << endl;
    Student *temp = first;
    while (temp != NULL)
    {
        cout << temp->regNum << "\tName: " << temp->name << ")"
             << "-> " << endl;
        temp = temp->next;
    }
    cout << endl;
}

// Get Student details
void Stack::studentDetails(string regNum)
{
    Student *_student = search(regNum);

    if (_student == NULL)
    {
        cout << "No Student with that registration number found!" << endl;
        return;
    }
    _student->getStudentDetails(true);
}

// Edit student
void Stack::editStudent(string regNum)
{
    Student *_student = search(regNum);

    if (_student == NULL)
    {
        cout << "No Student with that registration number found!" << endl;
        return;
    }

    int option = 0;
    cout << "Editing Student " << endl
         << "[1] Edit Student profile\n"
         << "[2] Edit academic details\n"
         << "[0] Cancel\n";
    cin >> option;

    string *_name = new string;
    string *_regNum = new string;
    string *_gender = new string;
    int *_age = new int(0);
    bool valid = false;

    switch (option)
    {
    case 1:

        cout << "Editing Student profile... enter '/n' to keep old value or enter a new value to change" << endl;
        cout << "name: " << _student->name << " : ";
        cin >> *_name;

        while (!valid)
        {
            cout << "Registration number: " << _student->regNum << " : ";
            cin >> *_regNum;
            valid = !checkIfRegExist(*_regNum);
            if (!valid)
            {
                cout << "That registration number exists try again!" << endl;
            }
        }

        cout << "Gender [M/F]";
        cin >> *_gender;
        cout << "Age: " << _student->age << " : ";
        cin >> *_age;

        _student->editStudentProfile(*_name, *_regNum, *_gender, *_age);
        break;

    case 2:
        cout << "Editing academic details... enter '/n' to keep old value or enter a new value to change" << endl;
        cout << "course name: " << _student->course.name << " : ";
        cin >> *_name;
        cout << "course code: " << _student->course.code << " : ";
        cin >> *_regNum;
        _student->editStudentAcademics(*_name, *_regNum);

    default:
        cout << "Please enter a number or 0 to cancel." << endl;
        break;
    }
    delete _name;
    delete _regNum;
    delete _gender;
    delete _age;
}

// Read file
int Stack::readFile(vector<Student *> &students)
{
    std::cout << "Reading from file...\n";

    // Create a variable to hold the file
    std::ifstream inputFile;

    inputFile.open("students.csv");

    if (!inputFile.is_open())
    {
        std::cout << "Unable to open file";
        // You can now read from the file
        return 1;
    }
    std::cout << "File opened!" << std::endl;
    std::string *line = new std::string;
    std::string *field = new std::string;
    std::string *temp = new std::string;
    bool *unitFound = new bool(false);

    // Read a line from the file and
    // skip the header of the file
    std::getline(inputFile, *line);

    while (std::getline(inputFile, *line))
    {
        Student *student = new Student;
        // create a string stream in order to split it into fields
        std::stringstream inputString(*line);
        // std::cout << *line << "  --- THe line"<<std::endl;

        // use getline for each field
        // Registration Number
        std::getline(inputString, *field, ',');
        student->regNum = *field;
        // name
        std::getline(inputString, *field, ',');
        student->name = *field;

        // age
        std::getline(inputString, *field, ',');
        // convert the string to a short
        student->age = static_cast<short>(stoi(*field));

        // year
        std::getline(inputString, *field, ',');
        student->year = static_cast<short>(stoi(*field));

        // gender
        std::getline(inputString, *field, ',');
        student->gender = *field;

        // course name
        std::getline(inputString, *field, ',');
        student->course.name = *field;

        // course code
        std::getline(inputString, *field, ',');
        student->course.code = *field;

        // read the remaining fields and search for units
        while (std::getline(inputString, *field, ','))
        {
            if (*field == "/unit")
            {
                *unitFound = !*unitFound;
                continue;
            }
            else if (*unitFound)
            {
                // The name of the course
                *temp = *field;
                // The marks as a string
                std::getline(inputString, *field, ',');
                student->course.units[*temp] = stof(*field);
            }
        }
        // calculate the aggregate
        student->setAggregate();

        // Add the students in the array
        students.emplace_back(student);
    }
    inputFile.close();
    delete line;
    delete field;
    delete unitFound;
    delete temp;
    return 0;
}

// Read from file and add to stack
void Stack::loadData()
{
    vector<Student *> vec;
    readFile(vec);

    for (int i = 0; i < vec.size(); i++)
    {
        push(vec[i]);
    }
    vec.clear();
}

// Delete
void Stack::deleteStudent(string regNum)
{
    Student *_student = search(regNum);

    if (_student == NULL)
    {
        cout << "No Student with that registration number found!" << endl;
        return;
    }
    delete _student;
    cout << "Student deleted" << endl;
}

// Manage stack
void Stack::stackManager()
{
    int option;
    bool mode = false;
    string name, reg_num;
    do
    {
        cout << "What operation do you want to perform?"
             << "Select Option number. Enter 0 to exit." << endl
             << "1. Push()" << endl
             << "2. Pop()" << endl
             << "3. isEmpty()" << endl
             << "4. peek()" << endl
             << "5. count()" << endl
             << "6. display()" << endl
             << "7. Clear Screen()" << endl
             << "8. Search()" << endl
             << "9. sort()" << endl
             << "10. Edit()" << endl
             << "11. Delete()" << endl
             << "12. View Full Student details"
             << endl;
        cin >> option;
        Student *new_student = new Student();

        switch (option)
        {
        case 0:
            break;
        case 1:
            new_student->setupStudent();
            push(new_student);
            break;

        case 2:
            cout << "Pop Function Called - Poped Value: " << endl;

            new_student = pop();

            cout << "First student is: " << new_student->regNum << " " << new_student->name << endl;
            delete new_student;
            cout << endl;
            break;

        case 3:
            if (isEmpty())
                cout << "Stack is Empty" << endl;
            else
                cout << "Stack is not Empty" << endl;
            break;
        case 4:
            if (isEmpty())
            {
                cout << "Stack is Empty" << endl;
            }
            else
            {
                cout << "PEEK Function Called : " << endl;
                new_student = peek();
                cout << "TOP of Stack is: " << new_student->regNum << " " << new_student->name << endl;
            }
            break;

        case 5:
            cout << "Count Function Called: " << endl;
            cout << "No of Students in the Stack: " << count() << endl;
            break;
        case 6:
            cout << "Display Function Called - " << endl;
            display();
            cout << endl;
            break;
        case 7:
            system("cls");
            break;
        case 8:
            cout << "Search called -" << endl
                 << "Enter registration number: " << endl;
            cin >> reg_num;

            new_student = search(reg_num);
            if (new_student)
            {
                cout << "Student found- "
                     << new_student->regNum << " name: "
                     << new_student->name << endl;
                break;
            }
            cout << "Student not found!" << endl;
            delete new_student;
            break;
        case 9:
            cout << "Do you want to sort by registration[1] or by aggregate[0]";
            cin >> mode;
            cout << "Before sorting " << endl;
            display();
            sort(mode);
            cout << endl;
            cout << "After sorting " << endl;
            display();
            cout << endl;
            break;
        case 10:
            cout << "Enter the registration number of the student you want to edit." << endl;
            cin >> reg_num;
            editStudent(reg_num);
            break;
        case 11:
            cout << "Enter the registration number of student you want to delete" << endl;
            cin >> reg_num;
            deleteStudent(reg_num);
            break;
        case 12:
            cout << "Enter the registration number to get full details" << endl;
            cin >> reg_num;
            studentDetails(reg_num);

            break;

        default:
            cout << "Enter Proper Option number " << endl;
        }
    } while (option != 0);
}
