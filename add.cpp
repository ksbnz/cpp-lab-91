#include <iostream>
using namespace std;

class Student
{
private:
    char name[30];
    int rollNumber;
    float marks;

public:
    void inputDetails()
    {
        cout << "Enter student Name: ";
        cin >> name;

        cout << "Enter roll Number: ";
        cin >> rollNumber;

        cout << "Enter Marks: ";
        cin >> marks;
    }

    void displayDetails()
    {
        cout << "Student Name: " << name << endl;
        cout << "Roll Number: " << rollNumber << endl;
        cout << "Marks: " << marks << endl;
    }
};

int main()
{
    Student s;

    s.inputDetails();
    s.displayDetails();

    return 0;
}