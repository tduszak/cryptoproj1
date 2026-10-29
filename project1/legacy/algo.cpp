#include "algo.h"
#include <iostream>
#include <iomanip>

// finds the gcd and prints the Division Algorithm table
int findGcd(int a, int b)
{
    // values used in each row of the table
    int u1, u2, u3, v1, v2, v3, q;

    // saves old u values before updating the next row
    int oldu1, oldu2, oldu3;

    // starting values from the Division Algorithm table
    u1 = 1;
    v1 = 0;
    u2 = 0;
    v2 = 1;
    u3 = a;
    v3 = b;
    q = 0;

    // show which pair we are working with
    std::cout << "finding gcd of " << a << " and " << b << "\n";

    // print table headers
    std::cout
        << "|" << std::setw(10) << "u1"
        << "|" << std::setw(10) << "v1"
        << "|" << std::setw(10) << "u2"
        << "|" << std::setw(10) << "v2"
        << "|" << std::setw(10) << "u3"
        << "|" << std::setw(10) << "v3"
        << "|" << std::setw(10) << "q" << "|\n";

    // print the first row
    std::cout
        << "|" << std::setw(10) << u1
        << "|" << std::setw(10) << v1
        << "|" << std::setw(10) << u2
        << "|" << std::setw(10) << v2
        << "|" << std::setw(10) << u3
        << "|" << std::setw(10) << v3
        << "|" << std::setw(10) << q << "|\n";

    // keep making rows until v3 becomes zero
    while (v3 != 0)
    {
        // save current u values before changing them
        oldu1 = u1;
        oldu2 = u2;
        oldu3 = u3;

        // quotient for the current step
        q = u3 / v3;

        // old v values become the new u values
        u1 = v1;
        u2 = v2;
        u3 = v3;

        // calculate the new v values
        v1 = oldu1 - (q * v1);
        v2 = oldu2 - (q * v2);
        v3 = oldu3 - (q * v3);

        // print the new row
        std::cout
            << "|" << std::setw(10) << u1
            << "|" << std::setw(10) << v1
            << "|" << std::setw(10) << u2
            << "|" << std::setw(10) << v2
            << "|" << std::setw(10) << u3
            << "|" << std::setw(10) << v3
            << "|" << std::setw(10) << q << "|\n";
    }

    // final u3 is the gcd
    std::cout << "gcd is " << u3 << "\n";

    // u1 and u2 are x and y in ax + by = gcd
    std::cout << "with x = " << u1 << " and y = " << u2 << "\n";

    return 0;
}