#include <iostream>
#include <iomanip>

using namespace std;

// creates the Division Algorithm table and finds gcd(a, b)
void findGcd(long long a, long long b)
{
    // starting values from the table in the class notes
    long long u1 = 1, v1 = 0;
    long long u2 = 0, v2 = 1;
    long long u3 = a, v3 = b;
    long long q = 0;

    // used to save the current u values before updating a row
    long long oldU1, oldU2, oldU3;

    cout << "============================================================\n";
    cout << "Finding gcd of " << a << " and " << b << "\n\n";

    // print the table headings
    cout << setw(12) << "u1"
         << setw(12) << "v1"
         << setw(12) << "u2"
         << setw(12) << "v2"
         << setw(12) << "u3"
         << setw(12) << "v3"
         << setw(12) << "q" << '\n';

    // print the first row
    cout << setw(12) << u1
         << setw(12) << v1
         << setw(12) << u2
         << setw(12) << v2
         << setw(12) << u3
         << setw(12) << v3
         << setw(12) << q << '\n';

    // continue until the remainder becomes zero
    while (v3 != 0)
    {
        oldU1 = u1;
        oldU2 = u2;
        oldU3 = u3;

        // quotient for this step
        q = u3 / v3;

        // old v values become the new u values
        u1 = v1;
        u2 = v2;
        u3 = v3;

        // calculate the new v values
        v1 = oldU1 - q * v1;
        v2 = oldU2 - q * v2;
        v3 = oldU3 - q * v3;

        // print the new row
        cout << setw(12) << u1
             << setw(12) << v1
             << setw(12) << u2
             << setw(12) << v2
             << setw(12) << u3
             << setw(12) << v3
             << setw(12) << q << '\n';
    }

    // final u values give the gcd and Bezout coefficients
    cout << "\n";
    cout << "gcd(" << a << ", " << b << ") = " << u3 << '\n';
    cout << "x = " << u1 << '\n';
    cout << "y = " << u2 << '\n';

    // verify that ax + by equals the gcd
    cout << "Verification:\n";
    cout << a << "(" << u1 << ") + "
         << b << "(" << u2 << ") = "
         << a * u1 + b * u2 << "\n\n";
}

int main()
{
    // group information required at the top of the output
    cout << "MATH 4175 - Cryptography Project 1\n";
    cout << "Project 1 - Division Algorithm\n\n";
    cout << "Group 5\n\n";

    cout << "Group Members:\n";
    cout << "Nguyen Nguyen\n";
    cout << "Spencer Steadman\n";
    cout << "Tanishqa Gautam\n";
    cout << "Tyler Duszak\n\n";

    // three pairs required by the project
    findGcd(768336, 78192);
    findGcd(494752, 296864);
    findGcd(17601969, 2364768);

    return 0;
}