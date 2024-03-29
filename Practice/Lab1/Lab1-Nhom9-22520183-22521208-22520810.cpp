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
//* 1.1
//* Áp dụng biểu thức De Morgan, để được x & y -> ~x | ~y -> ~(~x | ~y) = x & y
int bitAnd(int x, int y)
{
    x = ~(~x | ~y);
    return x;
}
//* 1.2
//* Áp dụng công thức chuyển đổi số âm sang dạng bù 2, x = ~x + 1
int negative(int x)
{
    x = ~x + 1;
    return x;
}
//* 1.3
//* Để xóa byte thứ n, ta tạo mask = ~(0xFF << (n << 3)) là nếu ta muốn tắt n byte thì sẽ dịch trái 0xFF (1111 1111)
//*n* 2^3 bit sau đó not đảo bit lại để cho ra bit mask cần thiết để giữ lại, cuối cùng ta chỉ x & mask sẽ cho ra byte thứ n cần xóa

int clearByte(int x, int n)
{
    int mask = ~(0xFF << (n << 3));
    x = x & mask;
    return x;
}

//* 1.4
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
//* 1.5
//* Ta xét xem n là số âm hay dương bằng cách dịch qua phải 31 bits và xét. Sau đó dùng Mux thay if-else
//* Nếu n sau khi dịch phải 31 bits = 1 (tức là n âm) thì kết quả x dịch phải -n bits.
//* Nếu n sau khi dịch phải 31 bits = 0 (tức là n dương) thì kết quả x dịch trái n bits.
int mulpw2(unsigned int x, int n)
{
    x = ((n >> 31) & (x >> negative(n))) | (~(n >> 31) & (x << n));
    return x;
}

//* 2.3
//* Để check x âm hay dương ta dựa vào bit có trọng số cao nhất !(x >> 31) và x có bằng 0 hay không thì !x, để cho ra output
//* phù hợp là trả về 1 nếu x dương, trả về 0 nếu x âm hoặc =0 -> ta xor 2 vế lại sẽ cho ra output mong muốn
int isPositive(int x)
{
    return (!(x >> 31) ^ !x);
}
//* 2.1
//* Để kiểm tra x và y có trái dấu hay không, ta chỉ cần kiểm tra x ^ y có bằng 0 hay không
//* Vì nếu x và y tuy trái dấu nhưng không đối nhau nên ta cần !(x + y) để kiểm tra x + y có bằng 0 hay không ( số đối cộng nhau = 0)
//* Hàm isPositive sẽ output ra 1 nếu x^y dương -> trường hợp x,y cùng dương cùng âm và & !(x+y) sẽ xử lý để cho ra output =0 là 2 số không đối nhau
//* => Nếu x,y là 2 số đối -> !isPositive(x^y) = 1 và !(x+y) = 1 -> output = 1
int isOpposite(int x, int y)
{
    return (!isPositive(x ^ y)) & !(x + y);
}
//* 2.2
//* Để kiểm tra x có phải là bội của 8 hay không, ta chỉ cần kiểm tra 3 bit cuối của x có bằng 0 hay không
//* Bằng cách tạo mask = ~(0xFFFFFFFF << 3) để lấy 3 bit cuối cùng của x, sau đó ta & x với mask để lấy 3 bit cuối cùng
//* Sau đó ta sẽ xor 3 bit cuối với 0, nếu 3 bit cuối =0 thì output = 1, ngược lại output = 0
int is8x(int x)
{
    int mask = ~(0xFFFFFFFF << 3);
    x = x & mask;
    return !(x ^ 0);
}
//* 2.4
//* Để kiểm tra x có lớn hơn hoặc bằng 2^n hay không, ta chỉ cần kiểm tra x + (-2^n) có lớn hơn hoặc bằng 0 hay không
//* Bằng cách dùng mux thay if else, ta sẽ kiểm tra bit trọng số cao nhất của biến diff
//* -> nếu diff âm -> x < 2^n -> output = 0, ngược lại output = 1
int isGE2n(int x, int n)
{
    int diff = x + (negative(1 << n));
    x = ((diff >> 31) & 0) | (~(diff >> 31) & 1);
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