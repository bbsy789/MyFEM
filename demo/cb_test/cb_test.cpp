#include <iostream>

using namespace std;

int main()
{
    size_t A = 0b00111111;
    size_t B = 0b00000111;
    size_t C = A & B;
    cout << A << B << C << endl;
    return 0;
}