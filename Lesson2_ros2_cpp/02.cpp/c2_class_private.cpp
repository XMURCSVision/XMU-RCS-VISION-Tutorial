// 目标：学会构造函数

#include <iostream>
#include <string>
using namespace std;

class Person
{
public:
    Person(string name, int yearGrade, string hobby)
    {
        cout << "Person构造函数" << endl;
        this->m_name = name;
        this->m_gradeYear = yearGrade;
        this->m_hobby = hobby;
    }

    void PrintInfo()
    {
        cout << "name:" << this->m_name << endl;
        cout << "yearGrade:" << this->m_gradeYear << endl;
        cout << "hobby:" << this->m_hobby << endl;
    }

    // protected
    // 目前视觉代码里没有用上protected，暂时不讲

private:
    string m_name; // member
    string m_gradeYear;
    string m_hobby;
};

int main()
{
    Person p1("Yan", 24, "RM");

    p1.PrintInfo();
    return 0;
}