#include <stdio.h>
#include <math.h>

int main()
{
    long int x=0, y=0, gint=0, b=0, bin0=0, bin1=0, rev=0, bin2=0;
    double dec=0, bin=0, frac=0, a=0, bin3=0;
    int decsign=1;
    //Ask for user input
    printf("Enter a number in decimal format : ");
    scanf("%lf", &dec);
    if (dec < 0)
    {
        dec *= -1;
        decsign = -1;
    }
    gint = floor(dec);
    frac = dec - gint;
    //Converting integral part to binary
    x = gint;
    y = gint;
    for (int i = 0; y > 1; i++)
    {
        y /= 2;
        x = y % 2;
        bin0 += x * pow(10, i);
    }
    bin1 = 10*bin0 + gint%2; //integral part of binary
    //converting fractional part to binary
    a = frac;
    for (int i = 0; (a > 0) && (i < 10); i++)
    {
        a *= 2;
        b = floor(a);
        a -= b;
        rev += b * pow(10, i);
    }
    //Reverse digits of bin2
    long int rem=0;
    while (rev!=0)
    {
        rem = rev % 10;
        bin2 = bin2 * 10 + rem;
        rev /= 10;
    }
    //Final binary
    long int count=0, n=bin2;
    while (n!=0)
    {
        n /= 10;
        count++;
    }
    bin3 = bin2 / pow(10, count);
    bin = decsign * (bin1 + bin3);
    printf("Your number in binary format : %lf\n", bin);
    if (bin < 0)
    {
        printf("Negative sign means that the number you entered is negative.\n");
    }
}