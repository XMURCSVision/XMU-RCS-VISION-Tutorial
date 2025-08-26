// 目标：学会build

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

    void PrintInfo_Person()
    {
        cout << "name:" << this->m_name << endl;
        cout << "yearGrade:" << this->m_gradeYear << endl;
        cout << "hobby:" << this->m_hobby << endl;
    }

    // protected
    // 目前视觉代码里没有用上protected，暂时不讲

    string m_name;
    int m_gradeYear;
    string m_hobby;
};

class RMer : public Person
{
public:
    RMer(string name, int yearGrade, string hobby, string group)
        : Person(name, yearGrade, hobby) // 调用父类的构造函数
    {
        this->m_group = group;
        cout << "RMer Constructor" << endl;
    }
    ~RMer()
    {
        cout << "RMer Destructor" << endl;
    }

    void PrintInfo_RMer()
    {
        PrintInfo_Person();
        cout << "group:" << this->m_group << endl;
    }

private:
    string m_group;
};

int main()
{
    Person p1("Yan", 24, "RM");
    p1.PrintInfo_Person();

    RMer rm1("Yan", 24, "RM", "Vision");
    rm1.PrintInfo_Person();

    return 0;
}