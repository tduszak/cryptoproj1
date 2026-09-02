#include "algo.h"
#include <iostream>

int findGcd(int a, int b)
{
    int u1, u2, u3, v1, v2, v3, q;
    int oldu1, oldu2, oldu3;
    u1 = 1;
    v1 = 0;
    u2 = 0;
    v2 = 1;
    u3 = a;
    v3 = b;
    q = 0;
    std::cout <<u1 <<" "<<v1<<" "<<u2<< " "<<v2<<" "<<u3<<" "<<v3<<" "<<q<< "\n";
    
    while(v3 != 0)
    {
        oldu1 = u1;
        oldu2 = u2;
        oldu3 = u3;
        q = u3 / v3;
        u1 = v1;
        u2 = v2;
        u3 = v3;
        v1 = oldu1 - (q * v1);
        v2 = oldu2 - (q * v2);
        v3 = oldu3 - (q * v3);
        std::cout <<u1 <<" "<<v1<<" "<<u2<< " "<<v2<<" "<<u3<<" "<<v3<<" "<<q<< "\n";
    }

    std::cout << "gcd is " << u3 << "\n";
    std::cout << "with x = " << u1 << " and y = " << u2 << "\n";
    return 0;
}

