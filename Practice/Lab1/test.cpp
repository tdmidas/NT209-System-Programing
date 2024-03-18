#include <stdio.h>
#include <iostream>
using namespace std;
void PrintBits(unsigned int x)
{
    int i;
    for (i = 8 * sizeof(x) - 1; i >= 0; i--)
    {
        (x & (1 << i)) ? putchar('1') : putchar('0');
    }
    printf("\n");
}
void PrintBitsOfByte(unsigned int x)
{
    int i;
    for (i = 7; i >= 0; i--)
    {
        (x & (1 << i)) ? putchar('1') : putchar('0');
    }
    printf("\n");
}
int isPositive(int x)
{
    return ((x >> 31) & 1) ^ (!(x == 0));
}

int main()
{
    cout << !(-10) << endl;

    return 0;
}