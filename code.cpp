#include <bits/stdc++.h>
using namespace std;
int main()
{
    int a,b,gcd;
    cout<<"Enter First Number: ";
    cin>>a;
    cout<<"Enter Second Number: ";
    cin>>b;

    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }

    gcd = a;

    cout << "GCD is: " << gcd << endl;

    return 0;
}
