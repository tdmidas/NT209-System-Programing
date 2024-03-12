#include <stdio.h>
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
//* Áp dụng biểu thức De Morgan, để được x & y -> ~x | ~y -> ~(~x | ~y) = x & y
int bitAnd(int x, int y)
{
    x = ~(~x | ~y);
    return x;
}
//* Áp dụng công thức chuyển đổi số âm sang dạng bù 2, x = ~x + 1
int negative(int x)
{
    x = ~x + 1;
    return x;
}
//* Để xóa byte thứ n, ta tạo mask = ~(0xFF << (n << 3)) là nếu ta muốn tắt n byte thì sẽ dịch trái 0xFF (1111 1111)
//*n* 2^3 bit sau đó not đảo bit lại để cho ra bit mask cần thiết để giữ lại, cuối cùng ta chỉ x & mask sẽ cho ra byte thứ n cần xóa

int clearByte(int x, int n)
{
    int mask = ~(0xFF << (n << 3));
    x = x & mask;
    return x;
}

//* Đầu tiên, vì int chỉ lưu 32 bit nên khi giá trị n lớn hơn 31 thì ta dùng 31 + negative(n), dùng mux để thay if, else
//* -> nếu n< 0 thì dịch phải 31 để kiểm tra bit cao nhất nó =1 hay ko ->nó âm -> n>31, ngược lại bit =0 thì nó dương -> 0<=n<=31
//* x sẽ bằng chính nó do dù n có lớn hơn 32 bit thì nó vẫn sẽ bằng chính nó, sau đó ta tạo mask = ~(0xFFFFFFFF << n) để lấy n bit cuối cùng
int getnbit(int x, int n)
{
    int diff = 31 + negative(n);
    int mask = ~(0xFFFFFFFF << n);
    x = ((diff >> 31) & x) | (~(diff >> 31) & (x & mask));
    return x;
}
//* Ta xét xem n là số âm hay dương bằng cách dịch qua phải 31 bits và xét. Sau đó dùng Mux thay if-else
//* Nếu n sau khi dịch phải 31 bits = 1 (tức là n âm) thì kết quả x dịch phải -n bits.
//* Nếu n sau khi dịch phải 31 bits = 0 (tức là n dương) thì kết quả x dịch trái n bits.
int mulpw2(unsigned int x, int n)
{
    x = ((n >> 31) & (x >> negative(n))) | (~(n >> 31) & (x << n));
    return x;
}

int isOpposite(int x, int y)
{
    return x;
}

int is8x(int x)
{
    return x;
}

int isPositive(int x)
{
    return x;
}

int isGE2n(int x, int n)
{
    return x;
}

int main()
{
    int score = 0;
    // 1.1
    printf("1.1 bitAnd");
    if (bitAnd(3, -9) == (3 & -9) && bitAnd(1, 8) == (1 & 8))
    {
        printf("\tPass.");
        score += 1;
    }
    else
        printf("\tFailed.");

    // 1.2
    printf("\n1.2 negative");
    if (negative(0) == 0 && negative(9) == -9 && negative(-5) == 5)
    {
        printf("\tPass.");
        score += 1;
    }
    else
        printf("\tFailed.");

    // 1.3
    printf("\n1.3 clearByte");
    if (clearByte(10, 0) == 0 && clearByte(20000, 1) == 32 && clearByte(0x12FE5501, 2) == 0x12005501)
    {
        printf("\tPass.");
        score += 2;
    }
    else
        printf("\tFailed.");

    // 1.4
    printf("\n1.4 getnbit");
    if (getnbit(15, 3) == 7 && getnbit(63, 6) == 63 && getnbit(30, 2) == 2)
    {
        if (getnbit(64, 32) == 64 && getnbit(-65000, 40) == -65000)
        {
            printf("\tAdvanced Pass.");
            score += 3;
        }
        else
        {
            printf("\tPass.");
            score += 2.5;
        }
    }
    else
        printf("\tFailed.");

    // 1.5
    printf("\n1.5 mulpw2");
    if (mulpw2(10, -1) == 5 && mulpw2(15, -2) == 3 && mulpw2(50, -2) == 12)
    {
        if (mulpw2(10, 1) == 20 && mulpw2(5, 4) == 80)
        {
            printf("\tAdvanced Pass.");
            score += 3;
        }
        else
        {
            printf("\tPass.");
            score += 2;
        }
    }
    else
        printf("\tFailed.");

    // 2.1
    printf("\n2.1 isOpposite");
    if (isOpposite(2, -2) == 1 && isOpposite(5, -1) == 0 && isOpposite(0, 16) == 0 && isOpposite(-4, 4) == 1)
    {
        printf("\tPass.");
        score += 2;
    }
    else
        printf("\tFailed.");

    // 2.2
    printf("\n2.2 is8x");
    if (is8x(16) == 1 && is8x(23) == 0 && is8x(0) == 1)
    {
        printf("\tPass.");
        score += 2;
    }
    else
        printf("\tFailed.");

    // 2.3
    printf("\n2.3 isPositive");
    if (isPositive(16) == 1 && isPositive(0) == 0 && isPositive(-8) == 0)
    {
        printf("\tPass.");
        score += 3;
    }
    else
        printf("\tFailed.");

    // 2.4
    printf("\n2.4 isGE2n");
    if (isGE2n(12, 4) == 0 && isGE2n(8, 3) == 1 && isGE2n(15, 2) == 1)
    {
        printf("\tPass.");
        score += 3;
    }
    else
        printf("\tFailed.");

    printf("\n------\nYour score: %.1f", (float)score / 2);
    return 0;
}