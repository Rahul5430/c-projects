#include <stdio.h>
#include <math.h>

int main()
{
    long int x=0, y=0, gint=0, b=0, bin0=0, bin1=0, rev=0, bin2=0;
    double dec=0, bin=0, frac=0, a=0, bin3=0;
    int decsign=1, slt=1, length=0;
    char hexaDecimal[100];
    //Ask for user input
    printf("Enter a number in decimal format : ");
    scanf("%lf", &dec);
    do
    {
        printf("(1) Binary (2) Octal (3) Hexadecimal : ");
        scanf("%d", &slt);
    } while ((slt != 1) && (slt != 2) && (slt != 3));
    if (slt == 1)
    {
        slt = 2;
    } else if (slt == 2)
    {
        slt = 8;
    } else
    {
        slt = 16;
    }
    if (dec < 0)
    {
        dec *= -1;
        decsign = -1;
    }
    gint = floor(dec);
    frac = dec - gint;
    //Converting integral part of decimal
    x = gint;
    y = gint;
    for (int i = 0; y > 0; i++)
    {
        x = y % slt;
        y /= slt;
        length = i+1;
        if (slt == 16)
        {
            if (x < 10)
            {
                hexaDecimal[i] = x + 48;
                continue;
            }
            else
            {
                hexaDecimal[i] = x + 55;
                continue;
            }
        }
        bin0 += x * pow(10, i);
    }
    //bin1 = 10*bin0 + gint%2; //integral part of binary
    if (slt == 16)
    {
        //int length = sizeof(hexaDecimal) / sizeof(char);
        printf("Your number in hexadecimal format is : ");
        for (int i=length-1; i >= 0; i--)
        {
            printf("%c", hexaDecimal[i]);
        }
    }
    else
    {
        //converting fractional part of decimal
        a = frac;
        for (int i = 0; (a > 0) && (i < 10); i++)
        {
            a *= slt;
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
        //Final conversion
        long int count=0, n=bin2;
        while (n!=0)
        {
            n /= 10;
            count++;
        }
        bin3 = bin2 / pow(10, count);
        bin = decsign * (bin0 + bin3);
        if (slt == 2)
        {
            printf("Your number in binary format : %lf\n", bin);
        }
        else
        {            
            printf("Your number in octal format : %lf\n", bin);
        }
        if (bin < 0)
        {
            printf("Negative sign means that the number you entered is negative.\n");
        }
    }
}