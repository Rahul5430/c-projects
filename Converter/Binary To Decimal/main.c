#include <stdio.h>
#include <math.h>

int main()
{
    long int bin1=0, dec1=0, binsign = 1;
    float bin, bin2=0, dec2=0, dec=0;
    int x=0, y=0;
    printf("Enter a Binary Number : ");
    scanf("%f", &bin);
    if (bin < 0)
    {
        binsign = -1;
        bin *= binsign;
    }
    bin1 = floor(bin);
    bin2 = bin - bin1;
    //Converting bin1 to decimal
    for (int i=0; bin1 > 0; i++)
    {
        x = bin1 % 10;
        bin1 /= 10;
        if (x == 1)
        {
            dec1 += pow(2, i);
        }
    }
    //Converting bin2 to decimal
    for (int i=0; bin2 > 0; i++)
    {
        bin2 *= 10;
        if ((floor(bin2) != 0) && (floor(bin2) != 1))
        {
            break;
        }
        if (floor(bin2) == 1)
        {
            dec2 += pow(2, -(i+1));
        }
        bin2 = bin2 - floor(bin2);
    }
    //Final Decimal
    dec = binsign * (dec1 + dec2);
    printf("%f\n", dec);
}