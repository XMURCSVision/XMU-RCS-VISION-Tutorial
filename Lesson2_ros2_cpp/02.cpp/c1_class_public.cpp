#include <iostream>
#include <string>
using namespace std;

// 目标：了解类和对象

class Person
{
public:
    Person()
    {
        cout << "Person Constructor" << endl;
    }
    ~Person()
    {
        cout << "Person Destructor" << endl;
    }

    void PrintInfo()
    {
        cout << "name:" << this->m_name << endl;
        cout << "yearGrade:" << this->m_gradeYear << endl;
        cout << "hobby:" << this->m_hobby << endl;
    }

    string m_name;
    string m_gradeYear;
    string m_hobby;
};

int main()
{
    Person p1;

    p1.m_name = "Yan";
    p1.m_gradeYear = 24;
    p1.m_hobby = "RM";

    p1.PrintInfo();
    return 0;
}