#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    int a, b, c;

    if (!(cin >> a >> b >> c)) {
        cout << "ЭТО НЕ ЧИСЛА!!!!";
        return 0;
    }
    
    if(a == 0)
    {
        cout << "На 0 делить нельзя";
        return 0;
    }
    
    double D = pow(b, 2) - 4 * a * c;
    
    
    if(D < 0)
    {
        cout << "Корней нет";
        return 0;
    }
    
    if(D == 0)
    {
        cout << (-b) / (2 * a);
    }
    else
    {
        D = sqrt(D);
        cout << (-b + D) / (2 * a) << " " << (-b - D) / (2 * a);
    }

    return 0;
}
