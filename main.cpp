#include "LANCopyWizard.h"
#include <QtWidgets>
#include <vector>
#include <algorithm> 
#include <iostream>
#include "Profiler.h"

namespace {
    class unique
    {
    public:
        double val = 0;
    };
    double val = 0;
    void b(double x)
    {
        val -= x;
    }
    void add_val(double x)
    {
        val += x;
        if (x == 0.01) b(0);
        if (x == 0.02) b(0.6);
        if (x == 0.03) b(-0.1);
        if (x == 0.04) b(0.4);
    }
}

//{
//    PROFILE_SCOPE("ADDVAL");
//    //PROFILE_SCOPE("ADDVAL");
//    unique u;
//    u.val = 0;
//    for (int i = 0; i < 1000000000; ++i)
//    {
//        add_val(i * 1e-10);
//    }
//}

class Base
{
public:
    // some virtual methods
    ~Base()
    {
        qDebug() << "DELETE BASE";
    }
};

class Derived : public Base
{
    ~Derived()
    {
        qDebug() << "DELETE DERIVED";
    }
};

//11 2 333/ 1 3333
//4 6 36 6 //длинна самой длинной последовательности из number
int find_range_n(const std::vector<int>& vec, int number)
{
    int result = 0;
    int counter = 0;
    for (size_t i = 0; i < vec.size();i++)
    {
        if (vec[i] == number)
        {
            counter++;
            result = std::max(result, counter);
        }
        else
            counter = 0;
    }
    result = std::max(result, counter);
    qDebug() << "RESULT" << result;
    return result;
}
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LANCopyWizard w;
    Base* b = new Derived();
    delete b;
    find_range_n({ 3,3,3,24,222,2,2444,12,90,3 },3);
    return a.exec();
}
